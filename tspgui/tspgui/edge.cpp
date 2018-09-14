#include "edge.h"

#include "node.h"
#include <QPainter>

Edge::Edge(Node *n1, Node *n2):
    n1_(n1), n2_(n2)
{
}

QRectF Edge::boundingRect() const {
    return QRectF(n1_->pos(), n2_->pos()).normalized();
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(QPen(Qt::black, 2));
    painter->drawLine(n1_->pos(), n2_->pos());
}
