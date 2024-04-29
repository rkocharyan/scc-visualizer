#include "graphwidget.h"
#include "utils.h"

#include <QMouseEvent>
#include <QMenu>
#include <QApplication>
#include <QInputDialog>
#include <QRandomGenerator>

GraphWidget::GraphWidget(QWidget *parent) : QGraphicsView(parent) {
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-5000, -5000, 10000, 10000);
    setScene(scene);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

QList <Node *> GraphWidget::nodes() const {
    return nodeList;
}

Node *GraphWidget::addNode(QPointF position, QString label = "") {
    qreal currentId = nodeId;
    nodeId++;
    Node *node = new Node(this, currentId, (label != "" ? label : QString::number(currentId)));

    scene()->addItem(node);
    node->setPos(position);

    nodeList << node;

    changeNodeCount();
    itemMoved();

    if (SCCMode) {
        runKosaraju(true);
    }

    return node;
}

void GraphWidget::removeNode(Node *node) {
    for (Edge *edge : node->edges()) {
        removeEdge(edge);
    }
    int index = nodeList.indexOf(node);
    if (index != -1) {
        nodeList.remove(index);
        changeNodeCount();
    }
    if (SCCMode) {
        runKosaraju(true);
    }
    scene()->removeItem(node);
}

void GraphWidget::addEdge(Node *source, Node *dest) {
    if (source->hasEdge(dest)) {
        return;
    }

    Edge *edge = new Edge(source, dest);
    scene()->addItem(edge);

    updateEdgeInfo(source->getLabel(), dest->getLabel());

    if (SCCMode) {
        runKosaraju(true);
    }
}

void GraphWidget::removeEdge(Edge *edge) {
    auto source = edge->sourceNode();
    auto dest = edge->destNode();

    auto sourceLabel = source->getLabel();
    auto destLabel = dest->getLabel();

    if (source) {
        source->removeEdge(edge);
    }
    if (dest) {
        dest->removeEdge(edge);
    }
    scene()->removeItem(edge);

    removeEdgeInfo(sourceLabel, destLabel);

    if (SCCMode) {
        runKosaraju(true);
    }
}

void GraphWidget::changeNodeCount() {
    qreal value = nodeList.length();
    emit nodeCountChanged(QString::number(value));
}

void GraphWidget::updateEdgeInfo(const QString &sourceLabel, const QString &destLabel) {
    QString text = sourceLabel + " " + destLabel;
    emit edgeAdded(text);
}

void GraphWidget::removeEdgeInfo(const QString &sourceLabel, const QString &destLabel) {
    QString text = sourceLabel + " " + destLabel;
    emit edgeRemoved(text);
}

void GraphWidget::renameNode(Node *node, QString newLabel) {
    QString previousLabel = node->getLabel();
    node->setLabel(newLabel);
    emit nodeRenamed(previousLabel, newLabel);
}

void GraphWidget::clearGraph() {
    for (auto node : std::as_const(nodeList)) {
        removeNode(node);
    }
    nodeId = 1;
}

void GraphWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidget::wheelEvent(QWheelEvent *event) {
    if (event->modifiers() & Qt::ControlModifier) {
        scaleView(pow(2., -event->angleDelta().y() / 240.0));
    } else {
        QGraphicsView::wheelEvent(event);
    }
}

void GraphWidget::stopDrawingEdge() {
    isDrawingEdge = false;
    clickedOnNode = false;
    nodeDragged = false;
    drawingEdgeStartNode = nullptr;
    update();
}

void GraphWidget::mousePressEvent(QMouseEvent *event) {
    if (currentMode != DrawingMode) {
        if (currentMode == DeletingMode) {
            if (event->button() == Qt::LeftButton) {
                QGraphicsItem *item = itemAt(event->pos());
                Node *node = qgraphicsitem_cast<Node *>(item);
                Edge *edge = qgraphicsitem_cast<Edge *>(item);
                if (node || edge) {
                    if (node) {
                        removeNode(node);
                    } else {
                        removeEdge(edge);
                    }
                } else {
                    QGraphicsView::mousePressEvent(event);
                }
            } else {
                QGraphicsView::mousePressEvent(event);
            }
            return;
        }

        QGraphicsView::mousePressEvent(event);
        return;
    }

    QPointF scenePos = mapToScene(event->pos());
    QGraphicsItem *item = itemAt(event->pos());
    Node *node = qgraphicsitem_cast<Node *>(item);

    if (event->button() == Qt::LeftButton) {
        if (!item) {
            if (!isDrawingEdge) {
                addNode(scenePos);
            } else {
                stopDrawingEdge();
            }
        } else {
            initialPressPosition = mapToScene(event->pos());
            if (node) {
                if (isDrawingEdge && node != drawingEdgeStartNode) {
                    addEdge(drawingEdgeStartNode, node);
                    stopDrawingEdge();
                } else {
                    clickedOnNode = true;
                    drawingEdgeStartNode = node;
                }
            } else {
                stopDrawingEdge();
            }
            QGraphicsView::mousePressEvent(event);
        }
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}
void GraphWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    if (currentMode != DrawingMode) {
        QGraphicsView::mouseDoubleClickEvent(event);
        return;
    }

    QPointF scenePos = mapToScene(event->pos());
    QGraphicsItem *item = itemAt(event->pos());
    Node *node = qgraphicsitem_cast<Node *>(item);

    if (event->button() == Qt::LeftButton) {
        if (!item) {
            if (!isDrawingEdge) {
                addNode(scenePos);
            } else {
                stopDrawingEdge();
            }
        } else {
            initialPressPosition = mapToScene(event->pos());
            if (node) {
                if (isDrawingEdge && node != drawingEdgeStartNode) {
                    addEdge(drawingEdgeStartNode, node);
                    stopDrawingEdge();
                } else {
                    clickedOnNode = true;
                    drawingEdgeStartNode = node;
                }
            } else {
                stopDrawingEdge();
            }
            QGraphicsView::mousePressEvent(event);
        }
    }
}

void GraphWidget::mouseMoveEvent(QMouseEvent *event) {
    if (currentMode != DrawingMode) {
        QGraphicsView::mouseMoveEvent(event);
        return;
    }

    QPointF curPosition = mapToScene(event->pos());
    if (event->button() == Qt::LeftButton && clickedOnNode && (initialPressPosition - curPosition).manhattanLength() > QApplication::startDragDistance()) {
        nodeDragged = true;
    }
    if (curPosition != currentMousePosition) {
        currentMousePosition = curPosition;
        update();
    }
    QGraphicsView::mouseMoveEvent(event);
}

void GraphWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (currentMode != DrawingMode) {
        QGraphicsView::mouseReleaseEvent(event);
        return;
    }

    QPointF releasePosition = mapToScene(event->pos());

    if (event->button() == Qt::LeftButton && clickedOnNode && (initialPressPosition - releasePosition).manhattanLength() > QApplication::startDragDistance()) {
        nodeDragged = true;
    }

    if (event->button() == Qt::LeftButton && clickedOnNode && !nodeDragged) {
        isDrawingEdge = true;
        update();
    }

    nodeDragged = false;
    QGraphicsView::mouseReleaseEvent(event);
}

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect) {
    QGraphicsView::drawBackground(painter, rect);

    if (isDrawingEdge && drawingEdgeStartNode) {
        QPen pen(Qt::black, 2);
        painter->setPen(pen);
        painter->drawLine(drawingEdgeStartNode->pos(), currentMousePosition);
    }
}

void GraphWidget::contextMenuEvent(QContextMenuEvent *event) {
    stopDrawingEdge();

    QPointF scenePoint = mapToScene(event->pos());
    QGraphicsItem* itemUnderCursor = scene()->itemAt(scenePoint, QTransform());

    QMenu contextMenu;
    if (itemUnderCursor) {
        Node *node = qgraphicsitem_cast<Node *>(itemUnderCursor);
        if (node) {
            QAction* relabelAction = contextMenu.addAction("Անվանափոխել");
            connect(relabelAction, &QAction::triggered, this, [this, node]{
                bool ok;
                QString newLabel = QInputDialog::getText(this, tr("Անուն"),
                                                         tr("Մուտքագրեք նոր անունը:"), QLineEdit::Normal,
                                                         node->getLabel(), &ok);
                if (ok && !newLabel.isEmpty()) {
                    renameNode(node, newLabel);
                }
            });
            if (currentMode == DrawingMode) {
                QAction* newEdgeAction = contextMenu.addAction("Նոր կող");
                connect(newEdgeAction, &QAction::triggered, this, [this, node, scenePoint]{
                    isDrawingEdge = true;
                    clickedOnNode = true;
                    drawingEdgeStartNode = node;
                    nodeDragged = false;
                    initialPressPosition = scenePoint;
                });
            }
        }
        contextMenu.addSeparator();
        QAction* deleteAction = contextMenu.addAction("Ջնջել");
        connect(deleteAction, &QAction::triggered, this, [this, itemUnderCursor]() {
            Node *node = qgraphicsitem_cast<Node *>(itemUnderCursor);
            Edge *edge = qgraphicsitem_cast<Edge *>(itemUnderCursor);
            if (node)
                removeNode(node);
            if (edge)
                removeEdge(edge);
        });
    } else {
        QAction* addAction = contextMenu.addAction("Նոր գագաթ");
        connect(addAction, &QAction::triggered, this, [this, scenePoint]() {
            addNode(scenePoint);
        });
    }

    contextMenu.exec(event->globalPos());
}

void GraphWidget::showEvent(QShowEvent *event) {
    QGraphicsView::showEvent(event);
    centerOn(0, 0);
}

void GraphWidget::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    centerOn(0, 0);
}

void GraphWidget::scaleView(qreal scaleFactor) {
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::zoomIn() {
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut() {
    scaleView(1 / qreal(1.2));
}

void GraphWidget::itemMoved() {
    if (currentMode != ForceMode) {
        if (timerId) {
            killTimer(timerId);
            timerId = 0;
        }
        return;
    }

    if (!timerId) {
        timerId = startTimer(1000 / 120);
    }
}

void GraphWidget::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);


    for (Node *node : std::as_const(nodeList)) {
        node->calculateForces(SCCMode);
    }

    bool anythingMoved = false;
    for (Node *node : std::as_const(nodeList)) {
        if (node->reposition()) {
            anythingMoved = true;
        }
    }

    if (!anythingMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}

void GraphWidget::setMode(Mode mode) {
    currentMode = mode;
    stopDrawingEdge();

    if (currentMode == ForceMode) {
        itemMoved();
    }
}

void GraphWidget::transpose() {
    QSet <Edge *> edges;
    for (const Node *node: std::as_const(nodeList)) {
        for (Edge *edge : node->edges()) {
            edges.insert(edge);
        }
    }
    for (Edge *edge : edges) {
        edge->transpose();
    }
    update();
}

void GraphWidget::topologicalSort(Node *node) {
    if (visited[node]) {
        return;
    }
    visited[node] = true;
    for (Edge *edge : node->edges()) {
        if (edge->sourceNode() == node) {
            topologicalSort(edge->destNode());
        }
    }
    topologicalOrder << node;
}

void GraphWidget::depthFirstSearch(Node *node) {
    if (color[node]) {
        return;
    }
    color[node] = curColor;
    for (Edge *edge : node->edges()) {
        if (edge->destNode() == node) {
            depthFirstSearch(edge->sourceNode());
        }
    }
}

void GraphWidget::runKosaraju(bool colored) {
    visited.clear();
    topologicalOrder.clear();
    for (Node *node : std::as_const(nodeList))  {
        topologicalSort(node);

    }
    std::reverse(topologicalOrder.begin(), topologicalOrder.end());
    color.clear();
    curColor = 0;
    for (Node *node : topologicalOrder) {
        if (color[node]) {
            continue;
        }
        curColor++;
        depthFirstSearch(node);
    }
    if (colored) {
        QList <QColor> colors = generateColors((int) nodeList.size());

        for (Node *node : std::as_const(nodeList)) {
            node->setColor(colors[color[node] - 1]);
            node->update();
        }
        update();
    }
}

void GraphWidget::switchSCCMode() {
    if (SCCMode) {
        for (Node *node : std::as_const(nodeList)) {
            node->setColor(Qt::black);
            node->update();
        }
        update();
    } else {
        runKosaraju(true);
    }
    SCCMode ^= 1;
    itemMoved();
}

void GraphWidget::createCondensationGraph() {
    runKosaraju(false);
    int compCnt = 0;
    for (Node *node : nodeList) {
        compCnt = std::max(compCnt, color[node]);
    }
    QVector <QSet <int> > adj(compCnt);
    for (Node *node : nodeList) {
        for (Edge *edge : node->edges()) {
            if (edge->sourceNode() == node) {
                if (color[edge->destNode()] != color[node]) {
                    adj[color[node] - 1].insert(color[edge->destNode()] - 1);
                }
            }
        }
    }
    clearGraph();
    for (int i = 0; i < compCnt; i++) {
        int x = QRandomGenerator::global()->bounded(0, (i + 1) * 10);
        int y = QRandomGenerator::global()->bounded(0, (i + 1) * 10);
        addNode(QPointF(x, y));
    }
    for (int i = 0; i < compCnt; i++) {
        for (const int& to : std::as_const(adj[i])) {
            addEdge(nodeList[i], nodeList[to]);
        }
    }
    if (SCCMode) {
        switchSCCMode();
    }
    setMode(ForceMode);
    itemMoved();
    centerOn(0, 0);
}
