/********************************************************************************
** Form generated from reading UI file 'algorithmpickerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALGORITHMPICKERDIALOG_H
#define UI_ALGORITHMPICKERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AlgorithmPickerDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QPushButton *kosarajuButton;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *tarjanButton;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *AlgorithmPickerDialog)
    {
        if (AlgorithmPickerDialog->objectName().isEmpty())
            AlgorithmPickerDialog->setObjectName("AlgorithmPickerDialog");
        AlgorithmPickerDialog->resize(300, 200);
        AlgorithmPickerDialog->setMinimumSize(QSize(300, 200));
        AlgorithmPickerDialog->setMaximumSize(QSize(300, 200));
        AlgorithmPickerDialog->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	font-weight: bold;\n"
"	font-size: 20px;\n"
"}\n"
"\n"
"QDialog {\n"
"	background-color: white;\n"
"}\n"
"\n"
"QPushButton {\n"
"	margin: 10px;\n"
"}"));
        verticalLayout = new QVBoxLayout(AlgorithmPickerDialog);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(AlgorithmPickerDialog);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font-weight: bold;"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 80, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        kosarajuButton = new QPushButton(AlgorithmPickerDialog);
        kosarajuButton->setObjectName("kosarajuButton");
        kosarajuButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	font-weight: bold;\n"
"	border-radius: 10px;\n"
"	border: 1px solid #2586db;\n"
"	background-color: #2586db;\n"
"	color: white;\n"
"	padding-left: 10px;\n"
"	padding-right: 10px;\n"
"	font-size: 16px;\n"
"	padding-top: 10px;\n"
"	padding-bottom: 10px;\n"
"	margin-bottom: 10px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: #73c5f5;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: #1490d9;\n"
"}"));

        verticalLayout->addWidget(kosarajuButton);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalSpacer = new QSpacerItem(40, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        tarjanButton = new QPushButton(AlgorithmPickerDialog);
        tarjanButton->setObjectName("tarjanButton");
        tarjanButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	font-weight: bold;\n"
"	border-radius: 10px;\n"
"	border: 1px solid #2e8f48;\n"
"	background-color: #2e8f48	;\n"
"	color: white;\n"
"	padding-left: 10px;\n"
"	padding-right: 10px;\n"
"	font-size: 16px;\n"
"	padding-top: 10px;\n"
"	padding-bottom: 10px;\n"
"	margin-bottom: 10px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: #75d191;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: #0acf46;\n"
"}"));

        verticalLayout->addWidget(tarjanButton);

        verticalSpacer_2 = new QSpacerItem(20, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        retranslateUi(AlgorithmPickerDialog);

        QMetaObject::connectSlotsByName(AlgorithmPickerDialog);
    } // setupUi

    void retranslateUi(QDialog *AlgorithmPickerDialog)
    {
        AlgorithmPickerDialog->setWindowTitle(QCoreApplication::translate("AlgorithmPickerDialog", "\324\261\325\254\325\243\325\270\326\200\325\253\325\251\325\264\325\253 \325\250\325\266\325\277\326\200\325\270\326\202\325\251\325\265\325\270\326\202\325\266", nullptr));
        label->setText(QCoreApplication::translate("AlgorithmPickerDialog", "\324\270\325\266\325\277\326\200\325\245\326\204 \325\241\325\254\325\243\325\270\326\200\325\253\325\251\325\264\325\250", nullptr));
        kosarajuButton->setText(QCoreApplication::translate("AlgorithmPickerDialog", "\324\277\325\270\325\275\325\241\326\200\325\241\325\265\325\270\326\202", nullptr));
        tarjanButton->setText(QCoreApplication::translate("AlgorithmPickerDialog", "\325\217\325\241\326\200\325\265\325\241\325\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AlgorithmPickerDialog: public Ui_AlgorithmPickerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALGORITHMPICKERDIALOG_H
