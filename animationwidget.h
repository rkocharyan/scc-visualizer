#ifndef ANIMATIONWIDGET_H
#define ANIMATIONWIDGET_H

#include "node.h"
#include "edge.h"
#include "stack.h"
#include "table.h"

#include <QGraphicsView>
#include <QList>
#include <QColor>

class Node;

class AnimationWidget : public QGraphicsView
{
    Q_OBJECT
public:
    AnimationWidget(QWidget *parent = nullptr);

    void drawGraph(QList <QString> nodeLabels, QList <std::pair <QString, QString> > edgeLabels);
    void redraw();
    void createTable();

    void createKosarajuFrames();
    void createTarjanFrames();
    int getFrameCount();

public slots:
    void updateFrame(int frame);
    void zoomIn();
    void zoomOut();

protected:
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    void scaleView(qreal scaleFactor);
    void topologicalSort(Node *node, Edge *parentEdge = nullptr);
    void depthFirstSearch(Node *node, QColor color);
    void tarjanDfs(Node *node, Edge *parentEdge = nullptr);
    void drawTitle(QString title);

private:
    struct FrameData {
        QString title;
        QMap <Node *, QColor> nodeColor;
        QMap <Edge *, QColor> edgeColor;
        QMap <Edge *, bool> edgeDashed;
        bool transposed;

        QList <QString> stack;
        QString addHighlightedStackElement;
        QString removeHighlightedStackElement;

        QMap <Node *, int> discovery, low;
        std::pair <QString, QString> addHighlightTableElement = {};
        std::pair <QString, QString> updateHighlightTableElement = {};
        std::pair <QString, QString> fromHighlightTableElement = {};
    };

    QList <FrameData> frames;
    QList <Node *> nodeList;

    QMap <Node *, bool> visited;
    QList <Node *> topologicalOrder;

    int currentFrame = 1;
    int totalFrames;

    const QColor visitedColor = Qt::blue;
    const QColor orderingColor = Qt::red;
    const QColor addHighlightColor = Qt::green;
    const QColor removeHighlightColor = Qt::red;
    const QColor updateHighlightColor = QColor("orange");
    const QColor fromHighlightColor = QColor("yellow");

    QRectF sceneRect, currentRect;
    QGraphicsTextItem *titleText = nullptr;

    int timer = 1;
    QMap <Node *, int> discovery, low;
    QMap <Node *, bool> onStack;
    QStack <Node *> nodeStack;

    QList <QColor> generatedColors;
    int currentColorIndex = 0;

    Stack *stack = nullptr;
    Table *table = nullptr;
};

#endif // ANIMATIONWIDGET_H
