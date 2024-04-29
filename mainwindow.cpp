#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "graphwidget.h"
#include "visualizationwindow.h"
#include "algorithmpickerdialog.h"

#include <QAction>
#include <QActionGroup>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();

    graph = this->findChild<GraphWidget*>("graphicsView");

    const GraphWidget::Mode drawingMode = GraphWidget::DrawingMode;
    const GraphWidget::Mode forceMode = GraphWidget::ForceMode;
    const GraphWidget::Mode deletingMode = GraphWidget::DeletingMode;

    connect(ui->actionDraw, &QAction::triggered, graph, [this, drawingMode]() {
        graph->setMode(drawingMode);
    });
    connect(ui->actionForce, &QAction::triggered, graph, [this, forceMode]() {
        graph->setMode(forceMode);
    });
    connect(ui->actionDelete, &QAction::triggered, graph, [this, deletingMode]() {
        graph->setMode(deletingMode);
    });

    QActionGroup *editGroup = new QActionGroup(this);
    editGroup->addAction(ui->actionDraw);
    editGroup->addAction(ui->actionForce);
    editGroup->addAction(ui->actionDelete);
    editGroup->setExclusive(true);
    ui->actionDraw->setChecked(true);

    ui->nodeCountText->setText(QString::number(0));

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFromFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveToFile);

    connect(ui->actionTranspose, &QAction::triggered, graph, [this]() {
        graph->transpose();
        transposeEdgeInfo();
    });
    connect(ui->actionClear, &QAction::triggered, graph, &GraphWidget::clearGraph);
    connect(ui->actionSCC, &QAction::triggered, graph, &GraphWidget::switchSCCMode);
    connect(ui->actionCondensationGraph, &QAction::triggered, this, &MainWindow::createCondensationGraph);
    connect(ui->actionVisualize, &QAction::triggered, this, &MainWindow::openVisualizationWindow);

    connect(graph, &GraphWidget::nodeCountChanged, this, &MainWindow::updateNodeCount);
    connect(graph, &GraphWidget::edgeAdded, this, &MainWindow::updateEdgeInfo);
    connect(graph, &GraphWidget::edgeRemoved, this, &MainWindow::removeEdgeInfo);
    connect(graph, &GraphWidget::nodeRenamed, this, &MainWindow::renameNode);

    connect(ui->graphGenerationButton, &QPushButton::clicked, this, &MainWindow::generateGraph);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateNodeCount(const QString &count) {
    ui->nodeCountText->setText(count);
}

void MainWindow::updateEdgeInfo(const QString &newEdge) {
    edgeData << newEdge;
    ui->edgesText->appendPlainText(newEdge);
}

void MainWindow::removeEdgeInfo(const QString &oldEdge) {
    if (!edgeData.contains(oldEdge)) {
        return;
    }
    edgeData.removeOne(oldEdge);
    ui->edgesText->clear();
    for (const QString& edgeInfo : std::as_const(edgeData)) {
        ui->edgesText->appendPlainText(edgeInfo);
    }
}

void MainWindow::renameNode(const QString &previousLabel, const QString &newLabel) {
    ui->edgesText->clear();
    for (QString& edgeInfo : edgeData) {
        QStringList nodes = edgeInfo.split(" ");
        QString source = nodes[0];
        QString dest = nodes[1];
        if (source == previousLabel) {
            source = newLabel;
        }
        if (dest == previousLabel) {
            dest = newLabel;
        }
        QString newEdgeInfo = source + " " + dest;
        edgeInfo = newEdgeInfo;
        ui->edgesText->appendPlainText(newEdgeInfo);
    }
}

void MainWindow::transposeEdgeInfo() {
    ui->edgesText->clear();
    for (QString& edgeInfo : edgeData) {
        QStringList nodes = edgeInfo.split(" ");
        QString source = nodes[1];
        QString dest = nodes[0];
        QString newEdgeInfo = source + " " + dest;
        edgeInfo = newEdgeInfo;
        ui->edgesText->appendPlainText(newEdgeInfo);
    }
}

void MainWindow::generateGraph() {
    QString allText = ui->edgesText->toPlainText();
    QStringList lines = allText.split("\n");

    QSet <QString> allNodesSet;

    for (const QString &line : lines) {
        QStringList words = line.split(" ");
        if (words.length() > 2) {
            continue;
        }
        for (const QString &word : words) {
            if (word == "") {
                continue;
            }
            allNodesSet.insert(word);
        }
    }
    graph->clearGraph();
    ui->edgesText->clear();

    QMap <QString, Node *> nodePtr;
    QStringList allNodes = QStringList(allNodesSet.begin(), allNodesSet.end());

    int cur = 1;
    for (const QString &nodeLabel : allNodes) {
        int x = QRandomGenerator::global()->bounded(0, cur * 10);
        int y = QRandomGenerator::global()->bounded(0, cur * 10);
        Node *node = graph->addNode(QPointF(x, y), nodeLabel);
        nodePtr[nodeLabel] = node;
        cur++;
    }

    for (const QString &line : lines) {
        QStringList words = line.split(" ");
        if (words.length() != 2) {
            continue;
        }
        QString sourceNode = words[0];
        QString destNode = words[1];
        if (sourceNode == "" || destNode == "") {
            continue;
        }
        Node *source = nodePtr[sourceNode];
        Node *dest = nodePtr[destNode];
        graph->addEdge(source, dest);
    }

    ui->actionForce->setChecked(true);
    graph->setMode(GraphWidget::ForceMode);
    graph->itemMoved();
    graph->centerOn(0, 0);
}

void MainWindow::createCondensationGraph() {
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Հաստատում");
    msgBox.setText("Համոզվա՞ծ եք, որ ուզում եք ստեղծել կոնդենսացիայի գրաֆը?");
    msgBox.setIcon(QMessageBox::Question);

    QAbstractButton *pButtonYes = msgBox.addButton("Այո", QMessageBox::YesRole);
    QAbstractButton *pButtonNo = msgBox.addButton("Ոչ", QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton() == pButtonYes) {
        graph->createCondensationGraph();
        ui->actionForce->setChecked(true);
        graph->setMode(GraphWidget::ForceMode);
        graph->itemMoved();
        graph->centerOn(0, 0);
        ui->actionSCC->setChecked(false);
    }
}

void MainWindow::openVisualizationWindow() {
    AlgorithmPickerDialog dialog;

    int value = dialog.exec();

    if (value != 1 && value != 2) {
        return;
    }

    VisualizationWindow::Algorithm algorithm = (value == 1 ? VisualizationWindow::Kosaraju : VisualizationWindow::Tarjan);

    VisualizationWindow *visWindow = new VisualizationWindow(algorithm, this);
    QList <QString> nodeLabels;
    QList <std::pair <QString, QString> > edgeLabels;
    for (Node *node : graph->nodes()) {
        nodeLabels << node->getLabel();
        for (Edge *edge : node->edges()) {
            if (edge->sourceNode() == node) {
                QString sourceLabel = node->getLabel();
                QString destLabel = edge->destNode()->getLabel();
                std::pair <QString, QString> edgeLabel = std::make_pair(sourceLabel, destLabel);
                edgeLabels << edgeLabel;
            }
        }
    }
    visWindow->drawGraph(nodeLabels, edgeLabels);
    visWindow->setAttribute(Qt::WA_DeleteOnClose);
    visWindow->show();
    visWindow->raise();
    visWindow->activateWindow();
}

void MainWindow::openFromFile() {
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Բացել"), "",
        tr("Text Files (*.txt);;All Files (*)")
    );

    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Չստացվեց բացել ֆայլը"), file.errorString());
        return;
    }

    QTextStream in(&file);
    QString fileContent = in.readAll();

    ui->edgesText->clear();
    ui->edgesText->appendPlainText(fileContent);
    generateGraph();
}

void MainWindow::saveToFile() {
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Պահպանել"), "",
        tr("Text Files (*.txt);;All Files (*)")
    );

    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Չստացվեց բացել ֆայլը"), file.errorString());
        return;
    }

    QTextStream out(&file);
    QString dataToSave;
    for (Node *node : graph->nodes()) {
        if (node->edges().empty()) {
            dataToSave += node->getLabel() + "\n";
        } else {
            for (Edge *edge : node->edges()) {
                if (edge->sourceNode() == node) {
                    dataToSave += node->getLabel() + " " + edge->destNode()->getLabel() + "\n";
                }
            }
        }
    }
    out << dataToSave;
}
