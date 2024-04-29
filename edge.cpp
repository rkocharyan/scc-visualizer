#include "edge.h"
#include "node.h"

#include <QPainter>

Edge::Edge(Node *source, Node *dest) : source(source), dest(dest) {
    setAcceptedMouseButtons(Qt::NoButton);
    source->addEdge(this);
    dest->addEdge(this);
    setZValue(-3);
    reposition();
}

Node *Edge::sourceNode() const {
    return source;
}

Node *Edge::destNode() const {
    return dest;
}

void Edge::reposition() {
    if (!source || !dest) {
        return;
    }

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > 2 * (source->borderSize + source->nodeRadius) - 1) {
        QPointF edgeOffset((line.dx() * source->nodeRadius) / length, (line.dy() * source->nodeRadius) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }
}

QRectF Edge::boundingRect() const {
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 2;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath Edge::shape() const {
    QPainterPath path;
    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return path;

    path.moveTo(line.p1());
    path.lineTo(line.p2());

    qreal penWidth = 2;
    QPen pen;
    pen.setWidthF(penWidth * 10);
    path = QPainterPathStroker(pen).createStroke(path);

    return path;
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    if (!source || !dest)
        return;

    if (transposed) {
        std::swap(sourcePoint, destPoint);
    }

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    QColor curColor = (source->getColor() == dest->getColor() ? source->getColor() : Qt::black);
    if (visualization) {
        curColor = color;
    }

    painter->setPen(QPen(curColor, 2, (dashed ? Qt::DashLine : Qt::SolidLine), Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

    painter->setPen(QPen(curColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    double angle = std::atan2(-line.dy(), line.dx());
    QPointF destArrowP1 = destPoint + QPointF(sin(angle - M_PI / 3) * arrowSize,
                                              cos(angle - M_PI / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                              cos(angle - M_PI + M_PI / 3) * arrowSize);

    painter->setBrush(curColor);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);

    if (transposed) {
        std::swap(sourcePoint, destPoint);
    }
}

void Edge::transpose() {
    std::swap(source, dest);
    reposition();
}

void Edge::setColor(QColor newColor) {
    color = newColor;
}

QColor Edge::getColor() {
    return color;
}

void Edge::setVisualizationMode() {
    visualization = true;
}

void Edge::setTransposed(bool status) {
    transposed = status;
}

void Edge::setDashed(bool status) {
    dashed = status;
}
