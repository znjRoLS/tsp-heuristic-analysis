#pragma once

#include <QGraphicsView>
#include <memory>
#include <world.h>
#include <state.h>
#include "node.h"
#include "edge.h"

using std::shared_ptr;
using TSP::World;
using TSP::State;
using TSP::Path;
using std::pair;

class TSPView : public QGraphicsView
{
public:
    TSPView(QWidget*&);
    void UpdateContents(const shared_ptr<World> world);
    void UpdateContents(const shared_ptr<State> state);
    // called only for second graphview_visualization
    void UpdateContents(const vector<pair<pair<int,int>, double>>& visuals);

    void SetEdgeColor(const QColor color);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void UpdateView();
    void ConstructNodes();
    void ConstructEdges();
    void AddNodes(shared_ptr<World> world);
    void AddEdges(Path& path);

    vector<QPointF> node_data_;
    vector<pair<pair<unsigned,unsigned>, double>> edge_data_;
    // Not shared pointer, since QT automatically deletes pointers to QWidgets
    vector<Node*> nodes_;
    vector<Edge*> edges_;
    shared_ptr<QGraphicsScene> scene_;
    QColor edge_color_;
};
