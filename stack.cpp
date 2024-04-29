#include "stack.h"

#include <QPainter>

Stack::Stack() {
    setFlag(ItemSendsGeometryChanges);
}

void Stack::push(QString &label, QColor color) {
    items.push(std::make_pair(label, color));
}

void Stack::pop() {
    if (!items.empty()) {
        items.pop();
    }
}

void Stack::clear() {
    items.clear();
}

void Stack::set(QList <QString> list) {
    clear();
    for (QString element : list) {
        push(element);
    }
}

void Stack::setColor(QString &label, QColor color) {
    for (int i = 0; i < (int) items.size(); i++) {
        if (items[i].first == label) {
            items[i].second = color;
        }
    }
}

qreal Stack::expectedHeight(int numItems) {
    return numItems * (itemHeight + spacing) + fontSize;
}

QRectF Stack::boundingRect() const {
    return QRectF(0, 0, itemWidth, (int) items.size() * (spacing + itemHeight) + fontSize);
}

QPainterPath Stack::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Stack::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    Q_UNUSED(option);

    if (items.empty()) {
        return;
    }

    painter->setPen(Qt::black);

    qreal currentHeight = spacing;
    for (int i = items.size() - 1; i >= 0; i--) {
        QRectF rect(0, currentHeight, itemWidth, itemHeight);
        painter->setBrush(items[i].second);
        painter->drawRect(rect);

        painter->setFont(QFont("Arial", fontSize));
        painter->drawText(rect, Qt::AlignCenter, items[i].first);

        currentHeight += itemHeight + spacing;
    }

    painter->drawText(QRectF(0, currentHeight, itemWidth, fontSize + spacing), Qt::AlignCenter, "Ստեկ");
}
