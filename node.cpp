#include "node.h"
#include "edge.h"
#include "graphwidget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QVector2D>

Node::Node(GraphWidget *graphWidget, qreal nodeId, QString label)
    : graph(graphWidget), nodeId(nodeId), label(label) {
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void Node::addEdge(Edge *edge) {
    if (edge->sourceNode() == this) {
        adjacentNodeIds[edge->destNode()->getId()] = edge;
    }
    edgeList << edge;
    edge->reposition();
    if (graph)
        graph->itemMoved();
}

void Node::removeEdge(Edge *edge) {
    int index = edgeList.indexOf(edge);
    if (index != -1) {
        if (edge->sourceNode() == this) {
            adjacentNodeIds.remove(edge->destNode()->getId());
        }
        edgeList.remove(index);
    }
    if (graph)
        graph->itemMoved();
}

QList <Edge *> Node::edges() const {
    return edgeList;
}

bool Node::hasEdge(Node *other) {
    return adjacentNodeIds.contains(other->getId());
}

Edge *Node::getEdge(Node *other) {
    return adjacentNodeIds[other->getId()];
}

int Node::getId() const {
    return nodeId;
}

QString Node::getLabel() const {
    return label;
}

void Node::setLabel(QString &text) {
    label = text;
    update();
}

QColor Node::getColor() {
    return color;
}

void Node::setColor(QColor newColor) {
    color = newColor;
}

void Node::setOrder(int order) {
    topologicalOrder = order;
}

QRectF Node::boundingRect() const {
    return QRectF(-nodeRadius - borderSize, -nodeRadius - borderSize, 2 * nodeRadius + 2 * borderSize, 2 * nodeRadius + 2 * borderSize);
}

QPainterPath Node::shape() const {
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Node::calculateForces(bool SCCMode) {
    if (!scene() || scene()->mouseGrabberItem() == this) {
        position = pos();
        return;
    }

    const qreal optimalDistanceNodes = 200;
    const qreal optimalDistanceEdges = 200;
    const qreal sccEdgeValue = 50;

    qreal xvel = 0;
    qreal yvel = 0;
    const QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        Node *node = qgraphicsitem_cast<Node *>(item);
        if (!node || node == this)
            continue;

        qreal curOptimalDistance = optimalDistanceNodes;

        if (SCCMode) {
            if (hasEdge(node)) {
                Edge *edge = getEdge(node);
                if (edge->sourceNode()->getColor() == edge->destNode()->getColor()) {
                    curOptimalDistance = sccEdgeValue;
                }
            } else if (node->hasEdge(this)) {
                Edge *edge = node->getEdge(this);
                if (edge->sourceNode()->getColor() == edge->destNode()->getColor()) {
                    curOptimalDistance = sccEdgeValue;
                }
            }
        }

        QPointF vec = mapToItem(node, 0, 0);
        qreal dx = vec.x();
        qreal dy = vec.y();
        double distSquared = dx * dx + dy * dy;
        double distance = sqrt(distSquared);

        if (distance < curOptimalDistance) {
            distance = std::max(distance, 1.);
            double forceMagnitude = 150.0 * (1 - distance / curOptimalDistance);
            xvel += (dx * forceMagnitude) / distSquared;
            yvel += (dy * forceMagnitude) / distSquared;
        }
    }
    double weight = (edgeList.size() + 1) * 10;
    for (const Edge *edge : std::as_const(edgeList)) {
        QPointF vec;
        Node *source = edge->sourceNode();
        Node *dest = edge->destNode();
        if (source->hasEdge(dest) && dest->hasEdge(source)) {
            if (edge->sourceNode() != this) {
                continue;
            }
        }
        if (edge->sourceNode() == this)
            vec = mapToItem(edge->destNode(), 0, 0);
        else
            vec = mapToItem(edge->sourceNode(), 0, 0);

        double distance = sqrt(vec.x() * vec.x() + vec.y() * vec.y());

        qreal curOptimalDistance = optimalDistanceEdges;
        if (SCCMode && edge->sourceNode()->getColor() == edge->destNode()->getColor()) {
            curOptimalDistance = sccEdgeValue;
        }

        if (distance > curOptimalDistance) {
            double forceMagnitude = (distance - curOptimalDistance) / weight;
            xvel -= vec.x() * forceMagnitude / distance;
            yvel -= vec.y() * forceMagnitude / distance;
        }
    }

    if (qAbs(xvel) < 0.1 && qAbs(yvel) < 0.1)
        xvel = yvel = 0;

    QPointF force = QPointF(xvel, yvel);

    position = pos() + force;
}

bool Node::reposition() {
    if (position == pos()) {
        return false;
    }

    setPos(position);
    return true;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    Q_UNUSED(option)

    QPen pen(color, borderSize);
    painter->setPen(pen);

    painter->setBrush(Qt::white);

    qreal diameter = 2 * nodeRadius;
    QRectF rect(-nodeRadius, -nodeRadius, diameter, diameter);
    painter->drawEllipse(rect);

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(18);
    painter->setFont(font);

    painter->setPen(color);

    painter->drawText(rect, Qt::AlignCenter, label);

    if (topologicalOrder) {
        QFont orderFont = painter->font();
        orderFont.setBold(false);
        orderFont.setPointSize(8);
        painter->setFont(orderFont);
        QRectF orderRect(-nodeRadius, nodeRadius / 3, diameter, nodeRadius / 2);
        painter->drawText(orderRect, Qt::AlignCenter, QString::number(topologicalOrder));
    }
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value) {
    switch (change) {
    case ItemPositionHasChanged:
        for (Edge *edge : std::as_const(edgeList))
            edge->reposition();
        if (graph)
            graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
