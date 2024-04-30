#include "animationwidget.h"
#include "utils.h"

#include <QRandomGenerator>
#include <QKeyEvent>

AnimationWidget::AnimationWidget(QWidget *parent) {
    QGraphicsScene *scene = new QGraphicsScene(this);
    setInteractive(true);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-5000, -5000, 10000, 10000);
    setScene(scene);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void AnimationWidget::drawGraph(QList <QString> nodeLabels, QList <std::pair <QString, QString> > edgeLabels) {
    nodeLabels.sort();

    QMap <QString, Node *> nodes;
    int id = 0;
    for (QString &label : nodeLabels) {
        Node *node = new Node(nullptr, id++, label);
        scene()->addItem(node);

        int x = QRandomGenerator::global()->bounded(0, id * 10);
        int y = QRandomGenerator::global()->bounded(0, id * 10);
        QPointF position(x, y);

        node->setPos(position);

        nodes[label] = node;
        nodeList << node;
    }

    for (auto& [sourceLabel, destLabel] : edgeLabels) {
        Edge *edge = new Edge(nodes[sourceLabel], nodes[destLabel]);
        scene()->addItem(edge);
        edge->setVisualizationMode();
    }

    const int MaxIterations = 100000000;
    for (int iter = 0; iter < MaxIterations; iter++) {
        for (Node *node : nodeList) {
            node->calculateForces(false);
        }
        bool itemMoved = false;
        for (Node *node : nodeList) {
            if (node->reposition()) {
                itemMoved = true;
            }
        }
        if (!itemMoved) {
            break;
        }
    }

    QRectF rect = scene()->itemsBoundingRect();
    qreal margin = 100;
    rect.adjust(-margin, -margin, margin, margin);

    sceneRect = rect;

    QCoreApplication::processEvents();
    fitInView(sceneRect, Qt::KeepAspectRatio);

    stack = new Stack();

    QRect viewportRect = viewport()->rect();
    currentRect = mapToScene(viewportRect).boundingRect();

    qreal height = stack->expectedHeight((int) nodeList.size()) + 2 * (int) nodeList.size();
    qreal width = 0;
    QPointF size = QPointF(width, height);
    QPointF topLeft = currentRect.bottomRight() - size;
    topLeft.setX(rect.bottomLeft().x());
    QRectF stackRect = QRectF(topLeft, rect.bottomRight());

    rect = rect.united(stackRect);

    sceneRect = rect;

    QCoreApplication::processEvents();
    fitInView(sceneRect, Qt::KeepAspectRatio);

    viewportRect = viewport()->rect();
    currentRect = mapToScene(viewportRect).boundingRect();

    scene()->addItem(stack);
}

void AnimationWidget::redraw() {
    int id = 1;
    for (Node *node : nodeList) {
        int x = QRandomGenerator::global()->bounded(0, id * 10);
        int y = QRandomGenerator::global()->bounded(0, id * 10);
        QPointF position(x, y);

        node->setPos(position);
        id++;
    }

    const int MaxIterations = 100000000;
    for (int iter = 0; iter < MaxIterations; iter++) {
        for (Node *node : nodeList) {
            node->calculateForces(false);
        }
        bool itemMoved = false;
        for (Node *node : nodeList) {
            if (node->reposition()) {
                itemMoved = true;
            }
        }
        if (!itemMoved) {
            break;
        }
    }

    bool addTable = false;

    if (stack)  scene()->removeItem(stack);
    if (titleText) scene()->removeItem(titleText);
    if (table) {
        scene()->removeItem(table);
        addTable = true;
    }

    titleText = nullptr;

    QRectF rect = scene()->itemsBoundingRect();
    qreal margin = 100;
    rect.adjust(-margin, -margin, margin, margin);

    sceneRect = rect;

    fitInView(sceneRect, Qt::KeepAspectRatio);

    stack = new Stack();

    QRect viewportRect = viewport()->rect();
    currentRect = mapToScene(viewportRect).boundingRect();

    qreal height = stack->expectedHeight((int) nodeList.size()) + 2 * (int) nodeList.size();
    qreal width = 0;
    QPointF size = QPointF(width, height);
    QPointF topLeft = currentRect.bottomRight() - size;
    topLeft.setX(rect.bottomLeft().x());
    QRectF stackRect = QRectF(topLeft, rect.bottomRight());

    rect = rect.united(stackRect);

    sceneRect = rect;

    fitInView(sceneRect, Qt::KeepAspectRatio);

    viewportRect = viewport()->rect();
    currentRect = mapToScene(viewportRect).boundingRect();

    scene()->addItem(stack);

    if (addTable) {
        createTable();
    }
}

void AnimationWidget::createTable() {
    QList <QString> columns = {"disc", "low"};
    QList <QString> labels;
    for (Node *node : nodeList) {
        labels << node->getLabel();
    }

    table = new Table(labels, columns);
    scene()->addItem(table);

    qreal height = table->boundingRect().height();
    QPointF offset = QPointF(currentRect.width() / 10, -(currentRect.height() - height) / 2 - height);

    table->setPos(currentRect.bottomLeft() + offset);
    table->update();
}

void AnimationWidget::topologicalSort(Node *node, Edge *parentEdge) {
    visited[node] = true;
    FrameData newFrame = frames.back();
    newFrame.nodeColor[node] = visitedColor;
    frames << newFrame;

    for (Edge *edge : node->edges()) {
        if (edge->sourceNode() == node) {
            Node *dest = edge->destNode();
            if (visited[dest]) {
                continue;
            }
            newFrame = frames.back();
            newFrame.edgeColor[edge] = visitedColor;
            frames << newFrame;
            topologicalSort(dest, edge);
        }
    }

    topologicalOrder << node;

    newFrame = frames.back();
    newFrame.nodeColor[node] = orderingColor;
    frames << newFrame;

    newFrame = frames.back();
    newFrame.stack << node->getLabel();
    newFrame.addHighlightedStackElement = node->getLabel();
    frames << newFrame;

    newFrame = frames.back();
    newFrame.addHighlightedStackElement = "";
    frames << newFrame;

    if (parentEdge != nullptr) {
        newFrame = frames.back();
        newFrame.edgeColor[parentEdge] = orderingColor;
        newFrame.edgeDashed[parentEdge] = true;
        frames << newFrame;
    }
}

void AnimationWidget::depthFirstSearch(Node *node, QColor color) {
    visited[node] = true;
    FrameData newFrame = frames.back();
    newFrame.nodeColor[node] = color;
    frames << newFrame;

    for (Edge *edge : node->edges()) {
        if (edge->destNode() == node) {
            if (visited[edge->sourceNode()]) {
                continue;
            }
            newFrame = frames.back();
            newFrame.edgeColor[edge] = color;
            frames << newFrame;
            depthFirstSearch(edge->sourceNode(), color);
        }
    }
}

void AnimationWidget::createKosarajuFrames() {
    frames << FrameData();

    if (nodeList.empty()) {
        frames << FrameData();
        totalFrames = 2;
        return;
    }

    FrameData newFrame = frames.back();
    newFrame.title = "Տոպոլոգիական սորտավորում";
    frames << newFrame;

    for (Node *node : nodeList) {
        if (!visited[node]) {
            topologicalSort(node);
        }
    }
    visited.clear();

    newFrame = frames.back();
    newFrame.title = "";
    newFrame.nodeColor.clear();
    newFrame.edgeColor.clear();
    newFrame.edgeDashed.clear();
    frames << newFrame;

    newFrame = frames.back();
    newFrame.title = "Կողերի շրջում";
    frames << newFrame;

    for (int i = 0; i < 2; i++) {
        newFrame = frames.back();
        newFrame.transposed = true;
        frames << newFrame;
    }

    newFrame = frames.back();
    newFrame.title = "";
    frames << newFrame;

    newFrame = frames.back();
    newFrame.title = "Փնտրում դեպի խորություն (DFS)";
    frames << newFrame;

    std::reverse(topologicalOrder.begin(), topologicalOrder.end());

    QList <QColor> colors = generateColors((int) nodeList.size());
    int currentColorIndex = 0;

    for (Node *node : topologicalOrder) {
        newFrame = frames.back();
        newFrame.removeHighlightedStackElement = node->getLabel();
        frames << newFrame;

        if (!visited[node]) {
            QColor currentColor = colors[currentColorIndex++];
            depthFirstSearch(node, currentColor);
        }

        newFrame = frames.back();
        newFrame.removeHighlightedStackElement = "";
        newFrame.stack.pop_back();
        frames << newFrame;
    }

    newFrame = frames.back();
    newFrame.title = "";
    frames << newFrame;

    newFrame = frames.back();
    newFrame.transposed = false;
    frames << newFrame;

    newFrame = frames.back();
    newFrame.edgeColor.clear();
    for (Node *node : nodeList) {
        for (Edge *edge : node->edges()) {
            if (newFrame.nodeColor[edge->sourceNode()] == newFrame.nodeColor[edge->destNode()]) {
                newFrame.edgeColor[edge] = newFrame.nodeColor[edge->sourceNode()];
            }
        }
    }
    frames << newFrame;

    totalFrames = frames.length();
}

void AnimationWidget::tarjanDfs(Node *node, Edge *parentEdge) {
    auto newFrame = frames.back();
    newFrame.nodeColor[node] = visitedColor;
    if (parentEdge) {
        newFrame.edgeColor[parentEdge] = Qt::black;
    }
    frames << newFrame;

    discovery[node] = low[node] = timer++;
    nodeStack.push(node);
    onStack[node] = true;

    newFrame = frames.back();
    newFrame.stack << node->getLabel();
    newFrame.addHighlightedStackElement = node->getLabel();
    frames << newFrame;

    newFrame = frames.back();
    newFrame.addHighlightedStackElement = "";
    frames << newFrame;

    newFrame = frames.back();
    newFrame.discovery[node] = discovery[node];
    newFrame.addHighlightTableElement = std::make_pair(node->getLabel(), "disc");
    frames << newFrame;

    newFrame = frames.back();
    newFrame.low[node] = low[node];
    newFrame.addHighlightTableElement = std::make_pair(node->getLabel(), "low");
    frames << newFrame;

    newFrame = frames.back();
    newFrame.low[node] = low[node];
    newFrame.addHighlightTableElement = {};
    frames << newFrame;

    for (Edge *edge : node->edges()) {
        if (edge->sourceNode() == node) {
            Node *dest = edge->destNode();
            if (discovery[dest] == -1) {
                newFrame = frames.back();
                newFrame.edgeColor[edge] = visitedColor;
                frames << newFrame;

                tarjanDfs(dest, edge);

                newFrame = frames.back();
                newFrame.updateHighlightTableElement = std::make_pair(node->getLabel(), "low");
                newFrame.nodeColor[node] = QColor("orange");
                frames << newFrame;

                newFrame = frames.back();
                newFrame.fromHighlightTableElement = std::make_pair(dest->getLabel(), "low");
                newFrame.edgeColor[edge] = QColor("yellow");
                frames << newFrame;

                low[node] = std::min(low[node], low[dest]);

                newFrame = frames.back();
                newFrame.low[node] = low[node];
                newFrame.addHighlightTableElement = std::make_pair(node->getLabel(), "low");
                newFrame.updateHighlightTableElement = {};
                newFrame.fromHighlightTableElement = {};
                newFrame.edgeColor[edge] = Qt::black;
                newFrame.nodeColor[node] = visitedColor;
                frames << newFrame;

                newFrame = frames.back();
                newFrame.low[node] = low[node];
                newFrame.addHighlightTableElement = {};
                frames << newFrame;
            } else if (onStack[dest]) {
                newFrame = frames.back();
                newFrame.nodeColor[node] = QColor("orange");
                newFrame.updateHighlightTableElement = std::make_pair(node->getLabel(), "low");
                frames << newFrame;

                newFrame = frames.back();
                newFrame.edgeColor[edge] = QColor("yellow");
                newFrame.edgeDashed[edge] = true;
                newFrame.fromHighlightTableElement = std::make_pair(dest->getLabel(), "low");
                frames << newFrame;

                low[node] = std::min(low[node], discovery[dest]);

                newFrame = frames.back();
                newFrame.low[node] = low[node];
                newFrame.addHighlightTableElement = std::make_pair(node->getLabel(), "low");
                newFrame.updateHighlightTableElement = {};
                newFrame.fromHighlightTableElement = {};
                newFrame.edgeColor[edge] = Qt::black;
                newFrame.edgeDashed[edge] = false;
                newFrame.nodeColor[node] = visitedColor;
                frames << newFrame;

                newFrame = frames.back();
                newFrame.low[node] = low[node];
                newFrame.addHighlightTableElement = {};
                frames << newFrame;
            }
        }
    }

    if (low[node] == discovery[node]) {
        newFrame = frames.back();
        newFrame.updateHighlightTableElement = std::make_pair(node->getLabel(), "low");
        newFrame.fromHighlightTableElement = std::make_pair(node->getLabel(), "disc");
        frames << newFrame;

        newFrame = frames.back();
        newFrame.updateHighlightTableElement = {};
        newFrame.fromHighlightTableElement = {};
        frames << newFrame;

        QColor currentColor = generatedColors[currentColorIndex++];

        while (true) {
            auto topNode = nodeStack.top();

            newFrame = frames.back();
            newFrame.removeHighlightedStackElement = topNode->getLabel();
            frames << newFrame;

            newFrame = frames.back();
            newFrame.removeHighlightedStackElement = "";
            newFrame.stack.pop_back();
            newFrame.nodeColor[topNode] = currentColor;
            frames << newFrame;

            onStack[topNode] = false;

            nodeStack.pop();

            if (topNode == node) {
                break;
            }
        }
    }
}

void AnimationWidget::createTarjanFrames() {
    createTable();

    frames << FrameData();

    if (nodeList.empty()) {
        frames << FrameData();
        totalFrames = 2;
        return;
    }

    for (Node *node : nodeList) {
        discovery[node] = low[node] = -1;
    }

    generatedColors = generateColors((int) nodeList.size());

    timer = 1;

    for (Node *node : nodeList) {
        if (discovery[node] == -1) {
            tarjanDfs(node);
        }
    }

    FrameData newFrame = frames.back();
    newFrame.edgeColor.clear();
    for (Node *node : nodeList) {
        for (Edge *edge : node->edges()) {
            if (newFrame.nodeColor[edge->sourceNode()] == newFrame.nodeColor[edge->destNode()]) {
                newFrame.edgeColor[edge] = newFrame.nodeColor[edge->sourceNode()];
            }
        }
    }
    frames << newFrame;

    totalFrames = frames.size();
}

void AnimationWidget::updateFrame(int frame) {
    FrameData frameData = frames[frame - 1];
    currentFrame = frame;
    for (Node *node : nodeList) {
        if (frameData.nodeColor.contains(node)) {
            node->setColor(frameData.nodeColor[node]);
        } else {
            node->setColor(Qt::black);
        }
        node->update();
        for (Edge *edge : node->edges()) {
            if (frameData.edgeColor.contains(edge)) {
                edge->setColor(frameData.edgeColor[edge]);
                edge->setZValue(-2);
            } else {
                edge->setColor(Qt::black);
                edge->setZValue(-3);
            }
            edge->setTransposed(frameData.transposed);
            edge->setDashed(frameData.edgeDashed[edge]);
            edge->update();
        }
        if (table == nullptr) {
            continue;
        }
        if (frameData.discovery.contains(node)) {
            table->setValue(node->getLabel(), "disc", frameData.discovery[node]);
        } else {
            table->setValue(node->getLabel(), "disc", -1);
        }
        if (frameData.low.contains(node)) {
            table->setValue(node->getLabel(), "low", frameData.low[node]);
        } else {
            table->setValue(node->getLabel(), "low", -1);
        }
        table->setColor(node->getLabel(), "disc", Qt::white);
        table->setColor(node->getLabel(), "low", Qt::white);
    }

    if (table) {
        if (frameData.addHighlightTableElement != std::pair<QString, QString>{}) {
            auto label = frameData.addHighlightTableElement.first;
            auto column = frameData.addHighlightTableElement.second;
            table->setColor(label, column, addHighlightColor);
        }

        if (frameData.updateHighlightTableElement != std::pair<QString, QString>{}) {
            auto label = frameData.updateHighlightTableElement.first;
            auto column = frameData.updateHighlightTableElement.second;
            table->setColor(label, column, updateHighlightColor);
        }

        if (frameData.fromHighlightTableElement != std::pair<QString, QString>{}) {
            auto label = frameData.fromHighlightTableElement.first;
            auto column = frameData.fromHighlightTableElement.second;
            table->setColor(label, column, fromHighlightColor);
        }
        table->update();
    }

    stack->set(frameData.stack);
    if (frameData.addHighlightedStackElement != "") {
        stack->setColor(frameData.addHighlightedStackElement, addHighlightColor);
    }
    if (frameData.removeHighlightedStackElement != "") {
        stack->setColor(frameData.removeHighlightedStackElement, removeHighlightColor);
    }

    qreal width = stack->boundingRect().width();
    qreal height = stack->boundingRect().height();
    qreal expectedHeight = stack->expectedHeight((int) nodeList.size());
    QPointF offset = QPointF(-currentRect.width() / 10 - width, -(currentRect.height() - expectedHeight) / 2 - height);

    stack->setPos(currentRect.bottomRight() + offset);
    stack->update();

    drawTitle(frameData.title);
    update();
}

void AnimationWidget::drawTitle(QString title) {
    if (!titleText) {
        titleText = new QGraphicsTextItem(title);
        QFont titleFont("Arial", 24, QFont::Bold);
        titleText->setFont(titleFont);
        titleText->setDefaultTextColor(Qt::black);
        scene()->addItem(titleText);
    } else {
        titleText->setPlainText(title);
    }

    QRectF bounds = titleText->boundingRect();
    qreal centerX = sceneRect.width() / 2 - bounds.width() / 2;
    qreal topY = sceneRect.top();

    titleText->setPos(sceneRect.left() + centerX, topY);
}

int AnimationWidget::getFrameCount() {
    return totalFrames;
}

void AnimationWidget::showEvent(QShowEvent *event) {
    QGraphicsView::showEvent(event);
    centerOn(0, 0);
}

void AnimationWidget::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    centerOn(0, 0);
}

void AnimationWidget::scaleView(qreal scaleFactor) {
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void AnimationWidget::zoomIn() {
    scaleView(qreal(1.2));
}

void AnimationWidget::zoomOut() {
    scaleView(1 / qreal(1.2));
}

void AnimationWidget::keyPressEvent(QKeyEvent *event) {
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
