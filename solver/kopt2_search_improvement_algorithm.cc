#include "kopt2_search_improvement_algorithm.h"

#include <algorithm>

using std::reverse;

#include "random.h"
#include "double_compare.h"

namespace TSP {

void Kopt2SearchImprovementAlgorithm::Reset() {
  current_search_first_edge_ = 0;
  current_search_second_edge_ = 2;
  reset_ = true;
}

bool Kopt2SearchImprovementAlgorithm::Iterate(int granularity) {

  int n = state_->current_path_.size() - 1;

  TSP_ASSERT(n >= 4);

  if (granularity == 2) {
    reset_ = false;

    if (enable_visuals_) {
      visualization_.clear();
    }

    int node_a = state_->current_path_[current_search_first_edge_];
    int node_b = state_->current_path_[current_search_first_edge_ + 1];
    int node_c = state_->current_path_[current_search_second_edge_];
    int node_d = state_->current_path_[current_search_second_edge_ + 1];

    double first_edge = (*state_->world_->distances_)[node_a][node_b];
    double second_edge = (*state_->world_->distances_)[node_c][node_d];
    double new_first_edge = (*state_->world_->distances_)[node_a][node_c];
    double new_second_edge = (*state_->world_->distances_)[node_b][node_d];

    if (DOUBLE_LESS(new_first_edge + new_second_edge, first_edge + second_edge)) {
      reverse(state_->current_path_.begin() + current_search_first_edge_ + 1,
              state_->current_path_.begin() + current_search_second_edge_ + 1);
      Reset();

      PushVisualEdge({node_a, node_b, GlobalColor::red, 0.5});
      PushVisualEdge({node_c, node_d, GlobalColor::red, 0.5});
      PushVisualEdge({node_a, node_c, GlobalColor::green, 1.0});
      PushVisualEdge({node_b, node_d, GlobalColor::green, 1.0});

      return true;
    } else {

      PushVisualEdge({node_a, node_b, GlobalColor::green, 1.0});
      PushVisualEdge({node_c, node_d, GlobalColor::green, 1.0});
      PushVisualEdge({node_a, node_c, GlobalColor::lightGray, 0.5});
      PushVisualEdge({node_b, node_d, GlobalColor::lightGray, 0.5});

      current_search_second_edge_++;
      // if the first edge is 0, second edge first invalid value is n-1, but otherwise its n;
      if ((current_search_first_edge_ >= 1 && current_search_second_edge_ == n)
          || (current_search_first_edge_ == 0 && current_search_second_edge_ == n - 1)) {

        // first invalid first_edge is when there's no valid value for second edge
        if (current_search_first_edge_ == n - 3) {
          return false;
        } else {
          current_search_first_edge_++;
          current_search_second_edge_ = current_search_first_edge_ + 2;
        }
      }
    }

  } else if (granularity == 1) {
    bool result = false;
    int last_first_edge = current_search_first_edge_;
    while (current_search_first_edge_ == last_first_edge) {
      result = Iterate(2);
      if (reset_) break;
      if (!result) break;
    }
    return result;
  } else if (granularity == 0) {
    while (Iterate(1)) {}
    return false;
  }

  return true;
}

int Kopt2SearchImprovementAlgorithm::GetMaxGranularity() {
  return 2;
}

} // namespace TSP