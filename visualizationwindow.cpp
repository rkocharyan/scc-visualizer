#include "visualizationwindow.h"
#include "ui_visualizationwindow.h"
#include "animationspeeddialog.h"

#include <QTimer>
#include <QStyle>

VisualizationWindow::VisualizationWindow(Algorithm algorithm, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VisualizationWindow)
    , algorithm(algorithm)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);
    showMaximized();

    ui->regenerateButton->setIcon(QIcon(":/images/images/reset.png"));
    ui->backwardButton->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->forwardButton->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    animation = this->findChild<AnimationWidget*>("animationArea");

    connect(ui->changeSpeedButton, &QPushButton::clicked, this, &VisualizationWindow::changeAnimationSpeed);
    connect(ui->regenerateButton, &QPushButton::clicked, this, &VisualizationWindow::regenerate);
}

VisualizationWindow::~VisualizationWindow()
{
    delete ui;
}

void VisualizationWindow::changeAnimationSpeed() {
    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    timer->stop();
    animationPlaying = false;

    AnimationSpeed dialog(currentSpeed);
    int speed = dialog.exec();

    if (speed != 0) {
        currentSpeed = speed;
        timer->setInterval(currentSpeed);
    }
}

void VisualizationWindow::drawGraph(QList <QString> nodeLabels, QList <std::pair <QString, QString> > edgeLabels) {
    nodeLabelsSaved = nodeLabels;
    edgeLabelsSaved = edgeLabels;

    animation->drawGraph(nodeLabels, edgeLabels);
    if (algorithm == Kosaraju) {
        animation->createKosarajuFrames();
    } else {
        animation->createTarjanFrames();
    }

    int frameCount = animation->getFrameCount();

    auto &slider = ui->animationSlider;

    slider->setMinimum(1);
    slider->setMaximum(frameCount);
    slider->setValue(1);

    timer = new QTimer();
    timer->setInterval(currentSpeed);

    connect(slider, &QSlider::valueChanged, this, [this] (int value) {
        animation->updateFrame(value);
    });

    connect(ui->backwardButton, &QPushButton::clicked, this, [this] {
        if (timer->isActive()) {
            ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            timer->stop();
            animationPlaying = false;
        }
        if (ui->animationSlider->value() - 1 >= ui->animationSlider->minimum()) {
            ui->animationSlider->setValue(ui->animationSlider->value() - 1);
        }
    });

    connect(ui->forwardButton, &QPushButton::clicked, this, [this] {
        if (timer->isActive()) {
            ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            timer->stop();
            animationPlaying = false;
        }
        if (ui->animationSlider->value() + 1 <= ui->animationSlider->maximum()) {
            ui->animationSlider->setValue(ui->animationSlider->value() + 1);
        }
    });

    connect(ui->playButton, &QPushButton::clicked, this, [this] {
        auto &slider = ui->animationSlider;
        if (!animationPlaying) {
            ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            if (slider->value() == slider->maximum()) {
                slider->setValue(slider->minimum());
            }
            timer->start();
            animationPlaying = true;
        } else {
            ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            timer->stop();
            animationPlaying = false;
        }
    });

    connect(timer, &QTimer::timeout, this, [this] {
        auto &slider = ui->animationSlider;
        if (slider->value() < slider->maximum()) {
            slider->setValue(slider->value() + 1);
        } else {
            timer->stop();
            ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            animationPlaying = false;
        }
    });
}

void VisualizationWindow::regenerate() {
    ui->animationSlider->setValue(ui->animationSlider->minimum());
    timer->stop();
    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    animationPlaying = false;
    animation->redraw();
}
