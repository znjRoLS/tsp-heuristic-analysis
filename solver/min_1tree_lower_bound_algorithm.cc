#include "min_1tree_lower_bound_algorithm.h"

#include "disjoint_set.h"
#include <map>
#include <limits>
#include "mst.h"

using std::map;
using std::numeric_limits;
using std::max;

namespace TSP {

void Min1treeLowerBoundAlgorithm::Reset() {
  current_node_ = 0;
  value_ = 0;
}

bool Min1treeLowerBoundAlgorithm::Iterate(int granularity) {

  if (granularity == 1) {

    int n = world_->size;
    auto mst = MST::Min1Tree(world_->distances_, current_node_);

    double total_weight = 0;
    for (auto& edge : mst) {
      total_weight += (*world_->distances_)[edge.first][edge.second];
    }

    visualization_.clear();
    for (auto& edge : mst) {
      if (edge.first == current_node_ || edge.second == current_node_) {
        visualization_.push_back({edge.first, edge.second, GlobalColor::green, 1.0});
      } else {
        visualization_.push_back({edge.first, edge.second, GlobalColor::green, 0.5});
      }
    }

    value_ = max(value_, total_weight);

    current_node_ ++;
    return current_node_ != n;

  } else if (granularity == 0) {
    while (Iterate(1));
    return false;
  }

  return true;
}

int Min1treeLowerBoundAlgorithm::GetMaxGranularity() {
  return 1;
}

} // namespace TSP