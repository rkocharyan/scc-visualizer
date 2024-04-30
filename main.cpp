#include "mainwindow.h"

#include <QApplication>
#include <QIcon>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    a.setWindowIcon(QIcon(":/images/images/graph.png"));

    MainWindow w;
    w.show();
    return a.exec();
}
