#include "table.h"

#include <QPainter>

Table::Table(QList <QString> labels, QList <QString> columns) : labels(labels), columns(columns) {
    setFlag(ItemSendsGeometryChanges);
}

void Table::setValue(QString label, QString column, int value) {
    data[label][column] = value;
}

void Table::setColor(QString  label, QString column, QColor color) {
    colors[label][column] = color;
}

QRectF Table::boundingRect() const {
    return QRectF(0, 0,
      labelFontSize + (int) columns.size() * cellWidth + margin,
      labelFontSize + (int) labels.size() * cellHeight + margin
    );
}

QPainterPath Table::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Table::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    Q_UNUSED(option);

    if (labels.empty() || columns.empty()) {
        return;
    }

    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black, 1);
    painter->setPen(pen);
    QFont labelFont("Arial", labelFontSize), valueFont("Arial", fontSize);

    qreal maxRowLabelWidth = 0;
    painter->setFont(labelFont);
    for (const QString &label : std::as_const(labels)) {
        maxRowLabelWidth = std::max(maxRowLabelWidth, (qreal) painter->fontMetrics().horizontalAdvance(label));
    }
    qreal rowLabelWidth = maxRowLabelWidth + 10;

    qreal currentY = labelFontSize + margin;
    for (const QString &label : std::as_const(labels)) {
        qreal currentX = rowLabelWidth + margin;
        for (const QString &column : std::as_const(columns)) {
            QRectF cellRect(currentX, currentY, cellWidth, cellHeight);
            QColor color = colors.value(label).value(column, Qt::white);
            painter->fillRect(cellRect, color);

            int value = data.value(label).value(column, -1);
            if (value != -1) {
                painter->drawText(cellRect, Qt::AlignCenter, QString::number(data[label][column]));
            }
            currentX += cellWidth;
        }
        currentY += cellHeight;
    }

    painter->setFont(labelFont);
    qreal labelX = rowLabelWidth + margin;
    for (const QString &column : std::as_const(columns)) {
        painter->drawText(QRectF(labelX, 0, cellWidth, labelFontSize), Qt::AlignCenter, column);
        labelX += cellWidth;
    }

    qreal labelY = labelFontSize + margin;
    for (const QString &label : std::as_const(labels)) {
        painter->drawText(QRectF(0, labelY, rowLabelWidth, cellHeight), Qt::AlignRight | Qt::AlignVCenter, label);
        labelY += cellHeight;
    }

    currentY = labelFontSize + margin;
    for (int i = 0; i <= labels.size(); i++) {
        painter->drawLine(rowLabelWidth + margin, currentY, rowLabelWidth + margin + columns.size() * cellWidth, currentY);
        currentY += cellHeight;
    }

    qreal currentX = rowLabelWidth + margin;
    for (int j = 0; j <= columns.size(); j++) {
        painter->drawLine(currentX, labelFontSize + margin, currentX, labelFontSize + margin + labels.size() * cellHeight);
        currentX += cellWidth;
    }
}
