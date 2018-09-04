#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class Node: public QGraphicsItem
{
public:
    Node(double rad);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    double radius = 5;
};

#endif // NODE_H
