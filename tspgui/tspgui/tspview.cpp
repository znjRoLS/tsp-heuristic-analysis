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

void TSPView::resizeEvent(QResizeEvent* event) {
    UpdateView();

    QGraphicsView::resizeEvent(event);
}

void TSPView::UpdateContents(shared_ptr<World> world) {

    node_pos_.clear();
    if (!world->nodes_->empty()) {
        Point2 minpt = (*world->nodes_)[0];
        Point2 maxpt = (*world->nodes_)[0];

        for (auto& point: (*world->nodes_)) {
            node_pos_.push_back(QPointF(point.x_, point.y_));
            minpt.x_ = min(minpt.x_, point.x_);
            minpt.y_ = min(minpt.y_, point.y_);
            maxpt.x_ = max(maxpt.x_, point.x_);
            maxpt.y_ = max(maxpt.y_, point.y_);
        }

        double scale_x = max(EPSILON, maxpt.x_ - minpt.x_);
        double scale_y = max(EPSILON, maxpt.y_ - minpt.y_);
        double scale_max = max(scale_x, scale_y);

        for (auto& point: node_pos_) {
            // Translate to (0,0)
            point.setX(point.x() - minpt.x_);
            point.setY(point.y() - minpt.y_);
            // Scale to (1,1)
            point.setX(point.x() / scale_max);
            point.setY(point.y() / scale_max);
        }
    }

    UpdateView();
}

void TSPView::UpdateView() {
    // This might not belong here, but its important to put it before scene_->clear(),
    // since scene clear deletes all pointers.
    nodes_.clear();
    scene_->clear();

    UpdateNodes();

    // Default behavior (when sceneRect is not set) is:
    // a rectangle that grows when items are added to or moved in the scene, but never shrinks.
    // Whyyyyyy?
    scene_->setSceneRect(scene_->itemsBoundingRect());
}

void TSPView::UpdateNodes() {
    QSize world_scale = 0.8 * size();

    for (auto& point: node_pos_) {
        QPointF scaled_point = point;
        scaled_point.setX(scaled_point.x() * world_scale.width());
        scaled_point.setY(scaled_point.y() * world_scale.height());
        Node* node = new Node(scaled_point, 5);
        nodes_.emplace_back(node);
        scene_->addItem(node);
    }
}
