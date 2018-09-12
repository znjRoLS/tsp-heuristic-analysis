#pragma once

#include <QGraphicsView>
#include <memory>
#include <world.h>
#include "node.h"

using std::shared_ptr;
using TSP::World;

class TSPView : public QGraphicsView
{
public:
    TSPView(QWidget*&);
    void UpdateContents(shared_ptr<World> world);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void UpdateView();
    void UpdateNodes();

    vector<QPointF> node_pos_;
    // Not shared pointer, since QT automatically deletes pointers to QWidgets
    vector<Node*> nodes_;
    shared_ptr<QGraphicsScene> scene_;
};
