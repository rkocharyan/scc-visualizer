#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include "node.h"
#include "edge.h"

#include <QGraphicsView>
#include <QList>

class Node;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = nullptr);

    Node *addNode(QPointF position, QString label);
    void addEdge(Node *source, Node *dest);

    void removeNode(Node *node);
    void removeEdge(Edge *edge);

    QList <Node *> nodes() const;
    void changeNodeCount();
    void updateEdgeInfo(const QString &sourceLabel, const QString &destLabel);
    void removeEdgeInfo(const QString &sourceLabel, const QString &destLabel);
    void renameNode(Node *node, QString newLabel);

    void transpose();
    void stopDrawingEdge();

    void itemMoved();

    enum Mode {
        DrawingMode,
        ForceMode,
        DeletingMode
    };

    void setMode(Mode mode);
    void runKosaraju(bool colored);

    void switchSCCMode();
    void createCondensationGraph();

signals:
    void nodeCountChanged(const QString &value);
    void edgeAdded(const QString &text);
    void edgeRemoved(const QString &text);
    void nodeRenamed(const QString &prevousLabel, const QString &newLabel);

public slots:
    void clearGraph();
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void scaleView(qreal scaleFactor);

    void topologicalSort(Node *node);
    void depthFirstSearch(Node *node);

private:
    QList <Node *> nodeList;

    QPointF initialPressPosition, currentMousePosition;
    bool isDrawingEdge = false;
    bool nodeDragged = false;
    bool clickedOnNode = false;
    Node *drawingEdgeStartNode;

    qreal timerId;
    int nodeId = 1;

    const qreal defaultTemperature = 1.0;

    Mode currentMode = DrawingMode;

    QMap <Node *, bool> visited;
    QMap <Node *, int> color;
    QList <Node *> topologicalOrder;
    int curColor = 0;

    bool SCCMode = false;
};

#endif // GRAPHWIDGET_H
