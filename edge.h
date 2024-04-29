#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

struct Node;

class Edge : public QGraphicsItem
{
public:
    Edge(Node *source, Node *dest);

    Node *sourceNode() const;
    Node *destNode() const;

    void reposition();
    void transpose();

    QColor getColor();
    void setColor(QColor color);

    void setVisualizationMode();
    void setTransposed(bool status);
    void setDashed(bool status);

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    Node *source, *dest;
    QPointF sourcePoint, destPoint;
    QColor color = Qt::black;

    const qreal arrowSize = 10;
    bool visualization = false;
    bool transposed = false;
    bool dashed = false;
};

#endif // EDGE_H
