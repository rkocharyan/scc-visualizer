#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>

class GraphWidget;
class Edge;

class Node : public QGraphicsItem
{
public:
    Node(GraphWidget *graphWidget, qreal nodeId, QString label);

    void addEdge(Edge *edge);
    void removeEdge(Edge *edge);
    QList <Edge *> edges() const;
    bool hasEdge(Node *other);
    Edge *getEdge(Node *other);

    int getId() const;
    QString getLabel() const;
    void setLabel(QString &text);

    QColor getColor();
    void setColor(QColor newColor);

    void setOrder(int order);

    void calculateForces(bool SCCMode);
    bool reposition();

    const qreal nodeRadius = 20;
    const qreal borderSize = 3;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    GraphWidget *graph;
    QPointF position;

    QList <Edge *> edgeList;
    QMap <int, Edge *> adjacentNodeIds;

    int nodeId;
    int topologicalOrder = 0;

    QString label;
    QColor color = Qt::black;
};

#endif // NODE_H
