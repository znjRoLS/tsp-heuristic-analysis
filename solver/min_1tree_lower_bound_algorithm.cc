#include "min_1tree_lower_bound_algorithm.h"

#include "disjoint_set.h"
#include <map>
#include <limits>

using std::map;
using std::numeric_limits;
using std::max;

namespace TSP {

void Min1treeLowerBoundAlgorithm::Reset() {
  current_node_ = 0;
}

bool Min1treeLowerBoundAlgorithm::Iterate(int granularity) {

  if (granularity == 1) {

    int n = world_->size;
    auto mst = MST(world_->distances_, current_node_);

    double min_weight = numeric_limits<double>::max();
    double second_min_weight = numeric_limits<double>::max();

    int min_node = current_node_;
    int second_min_node = current_node_;

    for (int i = 0; i < n; i ++) {
      if (i == current_node_) continue;

      double dist = (*world_->distances_)[current_node_][i];
      if (dist < min_weight) {
        second_min_node = min_node;
        second_min_weight = min_weight;
        min_weight = dist;
        min_node = i;
      } else if (dist < second_min_weight) {
        second_min_weight = dist;
        second_min_node = i;
      }
    }
    
    double total_weight = min_weight + second_min_weight;
    for (auto& edge : mst) {
      total_weight += (*world_->distances_)[edge.first][edge.second];
    }
    
    value_ = max(value_, total_weight);
    
    current_node_ ++;
    return current_node_ == n;

  } else if (granularity == 0) {
    while (Iterate(1));
    return false;
  }

  return true;
}

int Min1treeLowerBoundAlgorithm::GetMaxGranularity() {
  return 1;
}

unordered_set<pair<int, int>> Min1treeLowerBoundAlgorithm::MST(const shared_ptr<SquareMatrix<double>> distances, const int node_to_skip) const {
  int n = distances->size().first;
  DisjointSet disjoint_set(n);

  map<double, pair<int, int>> edges;

  for (int i = 0; i < n; i++) {
    if (i == node_to_skip) continue;
    for (int j = i + 1; j < n; j++) {
      if (j == node_to_skip) continue;
      edges.insert({(*distances)[i][j], {i, j}});
    }
  }

  unordered_set<pair<int, int>> chosen_edges;

  while (chosen_edges.size() != n - 2) {
    auto &edge = edges.begin()->second;

    if (!disjoint_set.SameSet(edge.first, edge.second)) {
      disjoint_set.Merge(edge.first, edge.second);

      chosen_edges.insert(edge);
    }

    edges.erase(edges.begin());
  }

  return chosen_edges;
}

} // namespace TSP