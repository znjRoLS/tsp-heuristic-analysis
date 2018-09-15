#pragma once

#include "QGraphicsItem"
#include "node.h"

class Edge : public QGraphicsItem
{
public:
    Edge(Node *n1, Node *n2, QColor color, double strength);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    Node* n1_;
    Node* n2_;
    QColor color_;
    double strength_;
};
