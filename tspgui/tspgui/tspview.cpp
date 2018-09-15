#include "tspview.h"
#include <QDebug>
#include "double_compare.h"

using std::min;
using std::max;
using std::make_shared;

TSPView::TSPView(QWidget*& widget):
    QGraphicsView (widget),
    scene_(make_shared<QGraphicsScene>()){

    setScene(scene_.get());
}

void TSPView::SetEdgeColor(QColor color) {
    edge_color_ = color;
}

void TSPView::resizeEvent(QResizeEvent* event) {
    UpdateView();

    QGraphicsView::resizeEvent(event);
}

void TSPView::AddNodes(shared_ptr<World> world) {
    if (world && !world->nodes_->empty()) {
        Point2 minpt = (*world->nodes_)[0];
        Point2 maxpt = (*world->nodes_)[0];

        for (auto& point: (*world->nodes_)) {
            node_data_.push_back(QPointF(point.x_, point.y_));
            minpt.x_ = min(minpt.x_, point.x_);
            minpt.y_ = min(minpt.y_, point.y_);
            maxpt.x_ = max(maxpt.x_, point.x_);
            maxpt.y_ = max(maxpt.y_, point.y_);
        }

        double scale_x = max(EPSILON, maxpt.x_ - minpt.x_);
        double scale_y = max(EPSILON, maxpt.y_ - minpt.y_);
        double scale_max = max(scale_x, scale_y);

        for (auto& point: node_data_) {
            // Translate to (0,0)
            point.setX(point.x() - minpt.x_);
            point.setY(point.y() - minpt.y_);
            // Scale to (1,1)
            point.setX(point.x() / scale_max);
            point.setY(point.y() / scale_max);
        }
    }
}

void TSPView::AddEdges(Path& path) {
    unsigned first = static_cast<unsigned>( path[0]);
    for (unsigned i = 1; i < path.size(); i ++) {
        unsigned second = static_cast<unsigned> ( path[i] );
        edge_data_.push_back({{first, second}, 1.0});
        first = second;
    }
}

void TSPView::UpdateContents(const shared_ptr<World> world) {
    node_data_.clear();
    edge_data_.clear();

    AddNodes(world);

    UpdateView();
}

void TSPView::UpdateContents(const shared_ptr<State> state) {
    node_data_.clear();
    edge_data_.clear();

    AddNodes(state->world_);
    AddEdges(state->current_path_);

    UpdateView();
}

void TSPView::UpdateContents(const vector<pair<pair<int,int>, double>>& visuals) {
    edge_data_.clear();
    for (auto& visual : visuals) {
        edge_data_.push_back(visual);
    }

    UpdateView();
}

void TSPView::UpdateView() {
    // This might not belong here, but its important to put it before scene_->clear(),
    // since scene clear deletes all pointers.
    // TODO: might be better to just update positions, and not actuall objects?
    edges_.clear();
    nodes_.clear();
    scene_->clear();

    ConstructNodes();
    ConstructEdges();

    // Default behavior (when sceneRect is not set) is:
    // a rectangle that grows when items are added to or moved in the scene, but never shrinks.
    // Whyyyyyy?
    scene_->setSceneRect(scene_->itemsBoundingRect());
}

void TSPView::ConstructNodes() {
    QSize world_scale = 0.8 * size();

    for (unsigned i = 0; i < node_data_.size(); i ++) {
        auto& point = node_data_[i];

        QPointF scaled_point = point;
        scaled_point.setX(scaled_point.x() * world_scale.width());
        scaled_point.setY(scaled_point.y() * world_scale.height());

        Node* node = new Node(scaled_point, 10);
        nodes_.emplace_back(node);

        QGraphicsSimpleTextItem* text_item = new QGraphicsSimpleTextItem(QString::number(i+1), node);
        text_item->setPos(-5, -5);

        scene_->addItem(node);
//        scene_->addItem(text_item);
    }
}

void TSPView::ConstructEdges() {
    for (unsigned i = 0; i < edge_data_.size(); i ++) {
        auto& edge_data = edge_data_[i];
        Node *n1 = nodes_[edge_data.first.first];
        Node *n2 = nodes_[edge_data.first.second];
        Edge *edge = new Edge(n1, n2, edge_color_, edge_data.second);
        edges_.push_back(edge);
        scene_->addItem(edge);

        QGraphicsSimpleTextItem* text_item = new QGraphicsSimpleTextItem(QString::number(i+1));
        text_item->setPos((n1->pos() + n2->pos())/2);
        scene_->addItem(text_item);
    }
}
