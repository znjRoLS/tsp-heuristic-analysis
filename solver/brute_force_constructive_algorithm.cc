#include "brute_force_constructive_algorithm.h"

#include <algorithm>
#include "state.h"
#include "container_contains.h"

using std::next_permutation;

namespace TSP {

void BruteForceConstructiveAlgorithm::Reset() {
  current_brute_force_path_.clear();

  for (int i = 0; i < world_->size; i++) {
    current_brute_force_path_.push_back(i);
  }
  current_brute_force_path_.push_back(0);

  current_path_ = current_brute_force_path_;

  current_path_cost_ = State::PathCost(current_brute_force_path_, world_->distances_);
}

bool BruteForceConstructiveAlgorithm::Iterate(int granularity) {

  if (granularity == 1) {
    if (!next_permutation(current_brute_force_path_.begin() + 1, current_brute_force_path_.end() - 1)) {
      return false;
    } else {
      double new_path_cost = State::PathCost(current_brute_force_path_, world_->distances_);
      if (new_path_cost < current_path_cost_) {
        current_path_cost_ = new_path_cost;
        current_path_ = current_brute_force_path_;
      }

      if (enable_visuals_) {
        SetVisuals();
      }

      return true;
    }
  } else if (granularity == 0) {
    while (Iterate(1));
    return false;
  }

  return true;
}

int BruteForceConstructiveAlgorithm::GetMaxGranularity() {
  return 1;
}

void BruteForceConstructiveAlgorithm::SetVisuals() {
  visualization_.clear();

  unordered_set<pair<int, int>> current_path_edges;
  int last = current_path_[0];
  for (unsigned nexti = 1; nexti < current_path_.size(); nexti++) {
    int next = current_path_[nexti];
    current_path_edges.insert({last, next});
    last = next;
  }

  last = current_brute_force_path_[0];
  for (unsigned nexti = 1; nexti < current_brute_force_path_.size(); nexti++) {
    int next = current_brute_force_path_[nexti];
    pair<int, int> edge = {last, next};
    pair<int, int> rev_edge = {next, last};
    if (CONTAINS(current_path_edges, edge) || CONTAINS(current_path_edges, rev_edge)) {
      current_path_edges.erase(edge);
      current_path_edges.erase(rev_edge);
      visualization_.push_back({edge.first, edge.second, GlobalColor::yellow, 1.0});
    } else {
      visualization_.push_back({edge.first, edge.second, GlobalColor::red, 0.5});
    }
    last = next;
  }

  for (auto &edge : current_path_edges) {
    visualization_.push_back({edge.first, edge.second, GlobalColor::green, 1.0});
  }
}

} // namespace TSP
