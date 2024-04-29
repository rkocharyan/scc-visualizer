#include "animationspeeddialog.h"
#include "ui_animationspeeddialog.h"

AnimationSpeed::AnimationSpeed(qreal currentSpeed, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AnimationSpeed)
{
    ui->setupUi(this);

    ui->verticalSlider->setMinimum(50);
    ui->verticalSlider->setMaximum(2000);
    ui->verticalSlider->setValue(currentSpeed);
    ui->label->setText(QString("Արագություն: %1մվ").arg(currentSpeed));

    ui->verticalSlider->setTickInterval(400);

    connect(ui->verticalSlider, &QSlider::valueChanged, this, [this](int value) {
        ui->label->setText(QString("Արագություն: %1մվ").arg(value));
    });

    connect(this, &QDialog::accepted, this, [this]() {
        setResult(ui->verticalSlider->value());
    });

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
}

AnimationSpeed::~AnimationSpeed()
{
    delete ui;
}
