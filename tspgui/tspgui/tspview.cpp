#include "tspview.h"

TSPView::TSPView(QWidget*& widget):
    QGraphicsView (widget) {}

void TSPView::update_contents(shared_ptr<World> world) {
     scene()->clear();

     for (auto Point2)
}
