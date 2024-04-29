/********************************************************************************
** Form generated from reading UI file 'visualizationwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VISUALIZATIONWINDOW_H
#define UI_VISUALIZATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "animationwidget.h"

QT_BEGIN_NAMESPACE

class Ui_VisualizationWindow
{
public:
    QVBoxLayout *verticalLayout;
    AnimationWidget *animationArea;
    QWidget *animationPlayer;
    QVBoxLayout *verticalLayout_2;
    QSlider *animationSlider;
    QWidget *animationButtons;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *buttonsLayout;
    QPushButton *regenerateButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *backwardButton;
    QPushButton *playButton;
    QPushButton *forwardButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *changeSpeedButton;
    QPushButton *saveButton;

    void setupUi(QWidget *VisualizationWindow)
    {
        if (VisualizationWindow->objectName().isEmpty())
            VisualizationWindow->setObjectName("VisualizationWindow");
        VisualizationWindow->resize(834, 459);
        VisualizationWindow->setStyleSheet(QString::fromUtf8("background-color: #f9f9f9;"));
        verticalLayout = new QVBoxLayout(VisualizationWindow);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        animationArea = new AnimationWidget(VisualizationWindow);
        animationArea->setObjectName("animationArea");
        animationArea->setStyleSheet(QString::fromUtf8("border: 0px;\n"
"background-color: white;"));

        verticalLayout->addWidget(animationArea);

        animationPlayer = new QWidget(VisualizationWindow);
        animationPlayer->setObjectName("animationPlayer");
        verticalLayout_2 = new QVBoxLayout(animationPlayer);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(-1, 0, -1, 0);
        animationSlider = new QSlider(animationPlayer);
        animationSlider->setObjectName("animationSlider");
        animationSlider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(animationSlider);

        animationButtons = new QWidget(animationPlayer);
        animationButtons->setObjectName("animationButtons");
        animationButtons->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: white;\n"
"}\n"
"\n"
"QPushButton::hover {\n"
"	background-color: #f9f9f9;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #f5f5f5;\n"
"}\n"
""));
        verticalLayout_3 = new QVBoxLayout(animationButtons);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        buttonsLayout = new QHBoxLayout();
        buttonsLayout->setSpacing(10);
        buttonsLayout->setObjectName("buttonsLayout");
        buttonsLayout->setContentsMargins(0, -1, 0, -1);
        regenerateButton = new QPushButton(animationButtons);
        regenerateButton->setObjectName("regenerateButton");
        regenerateButton->setMinimumSize(QSize(50, 50));
        regenerateButton->setMaximumSize(QSize(50, 50));
        regenerateButton->setStyleSheet(QString::fromUtf8("border: 2px solid black;"));

        buttonsLayout->addWidget(regenerateButton);

        horizontalSpacer = new QSpacerItem(60, 20, QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);

        buttonsLayout->addItem(horizontalSpacer);

        backwardButton = new QPushButton(animationButtons);
        backwardButton->setObjectName("backwardButton");
        backwardButton->setMinimumSize(QSize(50, 50));
        backwardButton->setMaximumSize(QSize(50, 50));
        backwardButton->setStyleSheet(QString::fromUtf8("border: 2px solid black;"));

        buttonsLayout->addWidget(backwardButton);

        playButton = new QPushButton(animationButtons);
        playButton->setObjectName("playButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(playButton->sizePolicy().hasHeightForWidth());
        playButton->setSizePolicy(sizePolicy);
        playButton->setMinimumSize(QSize(50, 50));
        playButton->setMaximumSize(QSize(50, 50));
        playButton->setStyleSheet(QString::fromUtf8("border: 2px solid black;"));

        buttonsLayout->addWidget(playButton);

        forwardButton = new QPushButton(animationButtons);
        forwardButton->setObjectName("forwardButton");
        forwardButton->setMinimumSize(QSize(50, 50));
        forwardButton->setMaximumSize(QSize(50, 50));
        forwardButton->setStyleSheet(QString::fromUtf8("border: 2px solid black;"));

        buttonsLayout->addWidget(forwardButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonsLayout->addItem(horizontalSpacer_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonsLayout->addItem(horizontalSpacer_3);

        changeSpeedButton = new QPushButton(animationButtons);
        changeSpeedButton->setObjectName("changeSpeedButton");
        changeSpeedButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: black;\n"
"    color: white;\n"
"    border: 2px solid white;\n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"    font-weight: bold;\n"
"    text-align: center;\n"
"    outline: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #333333; \n"
"    border-color: #f2f2f2;\n"
"    text-decoration: none;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #1a1a1a; \n"
"    border-color: #e6e6e6; \n"
"}\n"
""));

        buttonsLayout->addWidget(changeSpeedButton);

        saveButton = new QPushButton(animationButtons);
        saveButton->setObjectName("saveButton");
        saveButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: black;\n"
"    color: white;\n"
"    border: 2px solid white;\n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"    font-weight: bold;\n"
"    text-align: center;\n"
"    outline: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #333333; \n"
"    border-color: #f2f2f2;\n"
"    text-decoration: none;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #1a1a1a; \n"
"    border-color: #e6e6e6; \n"
"}\n"
""));

        buttonsLayout->addWidget(saveButton);

        buttonsLayout->setStretch(1, 13);
        buttonsLayout->setStretch(2, 5);
        buttonsLayout->setStretch(3, 5);
        buttonsLayout->setStretch(4, 5);
        buttonsLayout->setStretch(5, 6);
        buttonsLayout->setStretch(7, 3);
        buttonsLayout->setStretch(8, 3);

        verticalLayout_3->addLayout(buttonsLayout);


        verticalLayout_2->addWidget(animationButtons);


        verticalLayout->addWidget(animationPlayer);


        retranslateUi(VisualizationWindow);

        QMetaObject::connectSlotsByName(VisualizationWindow);
    } // setupUi

    void retranslateUi(QWidget *VisualizationWindow)
    {
        VisualizationWindow->setWindowTitle(QCoreApplication::translate("VisualizationWindow", "\324\261\325\254\325\243\325\270\326\200\325\253\325\251\325\264\325\253 \325\276\325\253\325\246\325\270\326\202\325\241\325\254\325\253\325\246\325\241\326\201\325\253\325\241", nullptr));
        regenerateButton->setText(QString());
        backwardButton->setText(QString());
        playButton->setText(QString());
        forwardButton->setText(QString());
        changeSpeedButton->setText(QCoreApplication::translate("VisualizationWindow", "\325\223\325\270\325\255\325\245\325\254 \325\241\326\200\325\241\325\243\325\270\326\202\325\251\325\265\325\270\326\202\325\266\325\250", nullptr));
        saveButton->setText(QCoreApplication::translate("VisualizationWindow", "\325\212\325\241\325\260\325\272\325\241\325\266\325\245\325\254", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VisualizationWindow: public Ui_VisualizationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VISUALIZATIONWINDOW_H
