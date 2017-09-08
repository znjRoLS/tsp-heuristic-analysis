#ifndef EDGE_H
#define EDGE_H


#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "node.h"

class Edge : public QGraphicsItem
{
public:
    Edge(Node *src, Node* dest);

    void adjust();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    Node *src, *dest;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
};

#endif // EDGE_H
