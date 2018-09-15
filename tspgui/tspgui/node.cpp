#include "node.h"
#include <QPainter>

Node::Node(QPointF& pos, double radius)
{
    r = radius;
    setPos(pos);
    setZValue(1);
}

QRectF Node::boundingRect() const
{
    return QRectF(-r, -r, 2*r, 2*r);
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::lightGray);
    painter->setPen(QPen(Qt::black, 0));
    painter->drawPath(shape());
}
