/********************************************************************************
** Form generated from reading UI file 'animationspeeddialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANIMATIONSPEEDDIALOG_H
#define UI_ANIMATIONSPEEDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AnimationSpeed
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QSlider *verticalSlider;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AnimationSpeed)
    {
        if (AnimationSpeed->objectName().isEmpty())
            AnimationSpeed->setObjectName("AnimationSpeed");
        AnimationSpeed->resize(176, 300);
        verticalLayout = new QVBoxLayout(AnimationSpeed);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(AnimationSpeed);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalSlider = new QSlider(widget);
        verticalSlider->setObjectName("verticalSlider");
        verticalSlider->setOrientation(Qt::Vertical);
        verticalSlider->setTickPosition(QSlider::TicksBelow);

        horizontalLayout->addWidget(verticalSlider);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(widget);

        label = new QLabel(AnimationSpeed);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font-weight: bold;"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        buttonBox = new QDialogButtonBox(AnimationSpeed);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(AnimationSpeed);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, AnimationSpeed, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, AnimationSpeed, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(AnimationSpeed);
    } // setupUi

    void retranslateUi(QDialog *AnimationSpeed)
    {
        AnimationSpeed->setWindowTitle(QCoreApplication::translate("AnimationSpeed", "\324\261\326\200\325\241\325\243\325\270\326\202\325\251\325\265\325\270\326\202\325\266", nullptr));
        label->setText(QCoreApplication::translate("AnimationSpeed", "\324\261\326\200\325\241\325\243\325\270\326\202\325\251\325\265\325\270\326\202\325\266: 800\325\264\325\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AnimationSpeed: public Ui_AnimationSpeed {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANIMATIONSPEEDDIALOG_H
