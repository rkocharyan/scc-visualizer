/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "graphwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionClear;
    QAction *actionDelete;
    QAction *actionDraw;
    QAction *actionForce;
    QAction *actionTranspose;
    QAction *actionCondensationGraph;
    QAction *actionSCC;
    QAction *actionVisualize;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *graphArea;
    QHBoxLayout *horizontalLayout;
    GraphWidget *graphicsView;
    QWidget *text2Graph;
    QVBoxLayout *verticalLayout_2;
    QLabel *nodeCountLabel;
    QLineEdit *nodeCountText;
    QLabel *edgesLabel;
    QPlainTextEdit *edgesText;
    QPushButton *graphGenerationButton;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menu;
    QMenu *menu_2;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1075, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("* {\n"
"	font-size: 15px;\n"
"	font-weight: 600;\n"
"}\n"
"\n"
"QMainWindow {\n"
"    background-color:  #f9f9f9;\n"
"}\n"
"\n"
"QToolBar, QMenuBar {\n"
"    background-color: #f9f9f9;\n"
"    border: 1px solid #e1e1e1;\n"
"}\n"
"\n"
"QMenuBar::item:selected, QToolBar::item:hover {\n"
"    background-color: #f0f0f0;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #ffffff;\n"
"    color: #333333;\n"
"    border: 2px solid #cccccc;\n"
"    border-radius: 4px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-color: #0078d7;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #cccccc;\n"
"}\n"
"\n"
"QTextEdit {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #cccccc;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QStatusBar {\n"
"    background-color: #ffffff;\n"
"    color: #333333;\n"
"}\n"
"\n"
"QScrollArea {\n"
"        border: none;\n"
"    }\n"
"\n"
"    QScrollBar {\n"
"        background: white;\n"
"        border-radius: 5px;\n"
"    }\n"
"\n"
"    QScroll"
                        "Bar:horizontal {\n"
"        height: 13px;\n"
"    }\n"
"\n"
"    QScrollBar:vertical {\n"
"        width: 13px;\n"
"    }\n"
"\n"
"    QScrollBar::handle {\n"
"        background: #3d3d3d;\n"
"        border-radius: 5px;\n"
"    }\n"
"\n"
"    QScrollBar::handle:horizontal {\n"
"        height: 25px;\n"
"        min-width: 10px;\n"
"    }\n"
"\n"
"    QScrollBar::handle:vertical {\n"
"        width: 25px;\n"
"        min-height: 10px;\n"
"    }\n"
"\n"
"    QScrollBar::add-line {\n"
"        border: none;\n"
"        background: none;\n"
"    }\n"
"\n"
"    QScrollBar::sub-line {\n"
"        border: none;\n"
"        background: none;\n"
"    }\n"
""));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon1);
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName("actionClear");
        actionClear->setCheckable(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/images/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear->setIcon(icon2);
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName("actionDelete");
        actionDelete->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/images/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete->setIcon(icon3);
        actionDraw = new QAction(MainWindow);
        actionDraw->setObjectName("actionDraw");
        actionDraw->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/images/draw.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDraw->setIcon(icon4);
        actionForce = new QAction(MainWindow);
        actionForce->setObjectName("actionForce");
        actionForce->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/images/move.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionForce->setIcon(icon5);
        actionTranspose = new QAction(MainWindow);
        actionTranspose->setObjectName("actionTranspose");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/images/transpose.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTranspose->setIcon(icon6);
        actionCondensationGraph = new QAction(MainWindow);
        actionCondensationGraph->setObjectName("actionCondensationGraph");
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/images/convert.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCondensationGraph->setIcon(icon7);
        actionSCC = new QAction(MainWindow);
        actionSCC->setObjectName("actionSCC");
        actionSCC->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/images/images/scc.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSCC->setIcon(icon8);
        actionVisualize = new QAction(MainWindow);
        actionVisualize->setObjectName("actionVisualize");
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/images/images/visualize.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionVisualize->setIcon(icon9);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        graphArea = new QWidget(centralwidget);
        graphArea->setObjectName("graphArea");
        horizontalLayout = new QHBoxLayout(graphArea);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 10, 0);
        graphicsView = new GraphWidget(graphArea);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setStyleSheet(QString::fromUtf8("border: 1px solid white;\n"
"background-color: white;"));

        horizontalLayout->addWidget(graphicsView);

        text2Graph = new QWidget(graphArea);
        text2Graph->setObjectName("text2Graph");
        text2Graph->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(text2Graph);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(-1, 24, -1, 24);
        nodeCountLabel = new QLabel(text2Graph);
        nodeCountLabel->setObjectName("nodeCountLabel");

        verticalLayout_2->addWidget(nodeCountLabel);

        nodeCountText = new QLineEdit(text2Graph);
        nodeCountText->setObjectName("nodeCountText");
        nodeCountText->setStyleSheet(QString::fromUtf8("border: 1px solid black;"));

        verticalLayout_2->addWidget(nodeCountText);

        edgesLabel = new QLabel(text2Graph);
        edgesLabel->setObjectName("edgesLabel");

        verticalLayout_2->addWidget(edgesLabel);

        edgesText = new QPlainTextEdit(text2Graph);
        edgesText->setObjectName("edgesText");
        edgesText->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
""));

        verticalLayout_2->addWidget(edgesText);

        graphGenerationButton = new QPushButton(text2Graph);
        graphGenerationButton->setObjectName("graphGenerationButton");
        graphGenerationButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        verticalLayout_2->addWidget(graphGenerationButton);


        horizontalLayout->addWidget(text2Graph);

        horizontalLayout->setStretch(0, 85);
        horizontalLayout->setStretch(1, 15);

        verticalLayout->addWidget(graphArea);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1075, 28));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        toolBar->setMinimumSize(QSize(0, 0));
        toolBar->setMaximumSize(QSize(16777215, 16777215));
        toolBar->setStyleSheet(QString::fromUtf8("QToolBar {\n"
"    spacing: 20px; \n"
"}\n"
"\n"
"QToolBar > QToolButton {\n"
"    margin-left: 5px;\n"
"    margin-right: 5px;\n"
"	margin-top: 1px;\n"
"}\n"
"\n"
"QToolBar > QToolButton:hover {\n"
"    background-color: #f0f0f0;	\n"
"	border: 0px;\n"
"}\n"
""));
        toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menu->addAction(actionForce);
        menu->addAction(actionDraw);
        menu->addAction(actionDelete);
        menu->addSeparator();
        menu->addAction(actionTranspose);
        menu->addAction(actionClear);
        menu_2->addAction(actionSCC);
        menu_2->addAction(actionCondensationGraph);
        toolBar->addAction(actionOpen);
        toolBar->addAction(actionSave);
        toolBar->addSeparator();
        toolBar->addAction(actionForce);
        toolBar->addAction(actionDraw);
        toolBar->addAction(actionDelete);
        toolBar->addSeparator();
        toolBar->addAction(actionTranspose);
        toolBar->addAction(actionClear);
        toolBar->addSeparator();
        toolBar->addAction(actionSCC);
        toolBar->addAction(actionCondensationGraph);
        toolBar->addAction(actionVisualize);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\324\277\325\270\325\266\325\244\325\245\325\266\325\275\325\241\326\201\325\253\325\241\325\265\325\253 \325\243\326\200\325\241\326\206\325\253 \326\207 \325\210\325\222\324\277\324\277 \325\276\325\253\325\246\325\270\326\202\325\241\325\254\325\253\325\246\325\241\325\277\325\270\326\200", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "\324\262\325\241\326\201\325\245\325\254", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "\325\212\325\241\325\260\325\272\325\241\325\266\325\245\325\254", nullptr));
        actionClear->setText(QCoreApplication::translate("MainWindow", "\325\204\325\241\326\204\326\200\325\245\325\254", nullptr));
        actionDelete->setText(QCoreApplication::translate("MainWindow", "\325\213\325\266\325\273\325\245\325\254", nullptr));
        actionDraw->setText(QCoreApplication::translate("MainWindow", "\325\206\325\257\325\241\326\200\325\245\325\254", nullptr));
        actionForce->setText(QCoreApplication::translate("MainWindow", "\325\207\325\241\326\200\325\252\325\245\325\254", nullptr));
        actionTranspose->setText(QCoreApplication::translate("MainWindow", "\325\207\326\200\325\273\325\245\325\254", nullptr));
        actionCondensationGraph->setText(QCoreApplication::translate("MainWindow", "\324\275\325\277\325\241\326\201\325\266\325\245\325\254", nullptr));
        actionSCC->setText(QCoreApplication::translate("MainWindow", "\325\210\325\222\324\277\324\277", nullptr));
        actionVisualize->setText(QCoreApplication::translate("MainWindow", "\324\261\325\254\325\243\325\270\326\200\325\253\325\251\325\264", nullptr));
        nodeCountLabel->setText(QCoreApplication::translate("MainWindow", "\324\263\325\241\325\243\325\241\325\251\325\266\325\245\326\200\325\253 \326\204\325\241\325\266\325\241\325\257", nullptr));
        edgesLabel->setText(QCoreApplication::translate("MainWindow", "\324\277\325\270\325\262\325\245\326\200", nullptr));
        graphGenerationButton->setText(QCoreApplication::translate("MainWindow", "\324\263\325\245\325\266\325\245\326\200\325\241\326\201\325\266\325\245\325\254", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "\325\226\325\241\325\265\325\254", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\325\223\325\270\326\203\325\270\325\255\325\245\325\254", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\324\261\325\254\325\243\325\270\326\200\325\253\325\251\325\264\325\266\325\245\326\200", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
