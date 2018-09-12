#pragma once

#include "QGraphicsItem"

class Node : public QGraphicsItem
{
public:
    Node(QPointF& pos, double rad);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    double r;

};
