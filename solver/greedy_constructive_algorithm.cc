#include "greedy_constructive_algorithm.h"

#include "container_contains.h"

using std::make_unique;

namespace TSP {

void GreedyConstructiveAlgorithm::Reset() {

  current_path_.clear();
  edges_.clear();
  selected_edges_.clear();
  node_degrees_.clear();
  disjoint_set_ = make_unique<DisjointSet>(world_->size);

  visualization_.clear();

  for(int i = 0 ; i < world_->size; i ++) {
    node_degrees_[i] = 0;
  }

  for (int i = 0; i < world_->size; i++) {
    for (int j = i + 1; j < world_->size; j++) {
      edges_.insert({(*world_->distances_)[i][j], {i, j}});
    }
  }

}

bool GreedyConstructiveAlgorithm::Iterate(int granularity) {

  if (granularity == 2) {

    if (!visualization_.empty() && visualization_.rbegin()->color == GlobalColor::green) {
      visualization_.rbegin()->color = GlobalColor::lightGray;
      visualization_.rbegin()->strength = 0.5;
    }
    if (!visualization_.empty() && visualization_.rbegin()->color == GlobalColor::red) {
      visualization_.pop_back();
    }

    // only the last edge left
    if (selected_edges_.size() + 1 == static_cast<unsigned>(world_->size)) {

      vector<int> nodes_left;
      for (auto& node : node_degrees_) {
        if (node.second == 1) {
          nodes_left.push_back(node.first);
        }
      }

      TSP_ASSERT_EQ(nodes_left.size(), 2);

      selected_edges_.insert({nodes_left[0], nodes_left[1]});

      visualization_.push_back({nodes_left[0], nodes_left[1], GlobalColor::lightGray, 0.5});

      TransformFinalPath();

      return false;
    }

    auto edge_iter = edges_.begin();

    auto &edge = edge_iter->second;

    if (node_degrees_[edge.first] != 2 && node_degrees_[edge.second] != 2 && !disjoint_set_->SameSet(edge.first, edge.second)) {
      selected_edges_.insert(edge);

      node_degrees_[edge.first] ++;
      node_degrees_[edge.second] ++;
      disjoint_set_->Merge(edge.first, edge.second);

      visualization_.push_back({edge.first, edge.second, GlobalColor::green, 1.0});

    } else {

      visualization_.push_back({edge.first, edge.second, GlobalColor::red, 0.5});
    }

    edges_.erase(edge_iter);

    return true;

  } else if (granularity == 1) {

    bool result = true;
    unsigned last_selected_edges = selected_edges_.size();
    while (last_selected_edges == selected_edges_.size()) {
      result = Iterate(2);
    }

    return result;

  } else if (granularity == 0) {
    while (Iterate(1));
    return false;
  }

  return true;
}

int GreedyConstructiveAlgorithm::GetMaxGranularity() {
  return 2;
}

void GreedyConstructiveAlgorithm::TransformFinalPath() {

 current_path_ = GetPathFromEdgeSet(selected_edges_);

}

} // namespace TSP
