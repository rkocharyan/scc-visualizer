#ifndef STACK_H
#define STACK_H

#include <QGraphicsItem>
#include <QStack>

class Stack : public QGraphicsItem
{
public:
    Stack();

    void push(QString &label, QColor color = QColor("#f9f9f9"));
    void pop();
    void clear();
    void set(QList <QString> list);
    void setColor(QString &lable, QColor color);

    qreal expectedHeight(int numItems);

    enum { Type = UserType + 3 };
    int type() const override { return Type; }

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QStack <std::pair <QString, QColor> > items;

    const qreal itemHeight = 20;
    const qreal itemWidth = 45;
    const qreal fontSize = 14;
    const qreal spacing = 6;

    const QColor defaultColor = QColor("#f9f9f9");
};

#endif // STACK_H
