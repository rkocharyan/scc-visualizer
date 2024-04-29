#ifndef VISUALIZATIONWINDOW_H
#define VISUALIZATIONWINDOW_H

#include "animationwidget.h"

#include <QWidget>

namespace Ui {
class VisualizationWindow;
}

class VisualizationWindow : public QWidget
{
    Q_OBJECT

public:
    enum Algorithm {
        Kosaraju,
        Tarjan
    };

    explicit VisualizationWindow(Algorithm algorithm, QWidget *parent = nullptr);
    ~VisualizationWindow();

    void drawGraph(QList <QString> nodeLabels, QList <std::pair <QString, QString> > edgeLabels);
    void regenerate();

protected:
    void changeAnimationSpeed();

private:
    Ui::VisualizationWindow *ui;

    AnimationWidget *animation;
    QTimer *timer;

    bool animationPlaying = false;
    qreal currentSpeed = 1000;

    Algorithm algorithm;

    QList <QString> nodeLabelsSaved;
    QList <std::pair <QString, QString> > edgeLabelsSaved;
};

#endif // VISUALIZATIONWINDOW_H
