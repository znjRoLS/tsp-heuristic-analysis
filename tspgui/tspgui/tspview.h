#pragma once

#include <QGraphicsView>
#include <memory>
#include <world.h>

using std::shared_ptr;
using TSP::World;

class TSPView : public QGraphicsView
{
public:
    TSPView(QWidget*&);

    void update_contents(shared_ptr<World> world);

private:
    vector<QPointF> nodes_;
};
