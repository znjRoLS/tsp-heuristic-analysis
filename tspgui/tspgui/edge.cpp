#include "edge.h"

#include "node.h"
#include <QPainter>

Edge::Edge(Node *n1, Node *n2, QColor color, double strength):
    n1_(n1), n2_(n2), color_(color), strength_(strength)
{
}

QRectF Edge::boundingRect() const {
    return QRectF(n1_->pos(), n2_->pos()).normalized();
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(QPen(color_, 4 * strength_));
    painter->drawLine(n1_->pos(), n2_->pos());
}
