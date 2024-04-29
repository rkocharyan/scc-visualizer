#ifndef TABLE_H
#define TABLE_H

#include <QGraphicsItem>

class Table : public QGraphicsItem
{
public:
    Table(QList <QString> labels, QList <QString> columns);

    void setValue(QString label, QString column, int value);
    void setColor(QString label, QString column, QColor color);

    enum { Type = UserType + 4 };
    int type() const override { return Type; }

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QMap <QString, QMap <QString, int> > data;
    QMap <QString, QMap <QString, QColor> > colors;
    QList <QString> labels, columns;

    const qreal cellWidth = 40;
    const qreal cellHeight = 25;
    const qreal fontSize = 14;
    const qreal labelFontSize = 14;
    const qreal margin = 5;
};

#endif // TABLE_H
