#pragma once

#include <QGraphicsView>
#include <memory>
#include <world.h>
#include <state.h>
#include "node.h"
#include "edge.h"
#include "util.h"

using std::shared_ptr;
using TSP::World;
using TSP::State;
using TSP::Path;
using std::pair;
using TSP::VisualEdge;

class TSPView : public QGraphicsView
{
public:
    TSPView(QWidget*&);
    void UpdateContents(const shared_ptr<World> world);
    void UpdateContents(const shared_ptr<State> state);
    // called only for second graphview_visualization
    void UpdateContents(const vector<VisualEdge>& visuals);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void UpdateView();
    void ConstructNodes();
    void ConstructEdges();
    void AddNodes(shared_ptr<World> world);
    void AddEdges(Path& path);

    vector<QPointF> node_data_;
    vector<VisualEdge> edge_data_;
    // Not shared pointer, since QT automatically deletes pointers to QWidgets
    vector<Node*> nodes_;
    vector<Edge*> edges_;
    shared_ptr<QGraphicsScene> scene_;
};
