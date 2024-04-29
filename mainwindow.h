#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

#include "graphwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateNodeCount(const QString &count);
    void updateEdgeInfo(const QString &newEdge);
    void removeEdgeInfo(const QString &oldEdge);
    void renameNode(const QString &previousLabel, const QString &newLabel);

    void transposeEdgeInfo();
    void createCondensationGraph();
    void generateGraph();
    void openVisualizationWindow();

    void openFromFile();
    void saveToFile();

private:
    Ui::MainWindow *ui;
    GraphWidget *graph;

    QList <QString> edgeData;
};
#endif // MAINWINDOW_H
