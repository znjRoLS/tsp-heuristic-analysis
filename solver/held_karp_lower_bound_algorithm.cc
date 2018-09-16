#include "held_karp_lower_bound_algorithm.h"

#include <memory>
#include <map>
#include <limits>
#include "square_matrix.h"
#include "disjoint_set.h"
#include "double_compare.h"

using std::map;
using std::make_shared;
using std::numeric_limits;
using std::max;

namespace TSP {

void HeldKarpLowerBoundAlgorithm::Reset() {
  distances_ = make_shared<SquareMatrix<double>>(world_->distances_);
  pi_ = vector<double>(world_->size, 0);
  current_node_ = 0;
  value_ = 0;
}

bool HeldKarpLowerBoundAlgorithm::Iterate(int granularity) {

  int n = world_->size;

  if (granularity == 2) {

    auto min1tree = Min1Tree(world_->distances_, current_node_);

    double total_weight = 0;
    for (auto& edge : min1tree) {
      total_weight += (*world_->distances_)[edge.first][edge.second];
    }

    if DOUBLE_GREATER(total_weight, value_) {
      value_ = total_weight;
      min_1tree_ = min1tree;
    }

    current_node_ ++;

    if (current_node_ == n) {
      current_node_ = 0;

      return IteratePi(min_1tree_);
    }

    return true;
  }

  return true;
}

int HeldKarpLowerBoundAlgorithm::GetMaxGranularity() {
  return 0;
}

bool HeldKarpLowerBoundAlgorithm::IteratePi(unordered_set<pair<int,int>> min_1tree) {
  int n = world_->size;

  vector<int> d (n, -2);

  for (auto& edge : min_1tree) {
    d[edge.first] --;
    d[edge.second] --;
  }
}

unordered_set<pair<int, int>> HeldKarpLowerBoundAlgorithm::Min1Tree(const shared_ptr<SquareMatrix<double>> distances, const int special_node) const {
  int n = distances->size().first;

  // get MST of /{special_node}
  int node_to_skip = special_node;

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

  // calculate two nearest
  int node = special_node;

  double min_weight = numeric_limits<double>::max();
  double second_min_weight = numeric_limits<double>::max();

  int min_node = node;
  int second_min_node = node;

  for (int i = 0; i < n; i ++) {
    if (i == node) continue;

    double dist = (*distances)[node][i];
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

  chosen_edges.insert({node, min_node});
  chosen_edges.insert({node, second_min_node});

  return chosen_edges;
}

}; // namespace TSP
