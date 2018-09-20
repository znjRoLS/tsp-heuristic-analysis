#include "kopt3_search_improvement_algorithm.h"

#include "double_compare.h"
#include "random.h"
#include <algorithm>

using std::swap;

namespace TSP {

void Kopt3SearchImprovementAlgorithm::Reset() {

  current_search_first_edge_ = 0;
  current_search_second_edge_ = 2;
  current_search_third_edge_ = 4;
  reset_ = true;
}

bool Kopt3SearchImprovementAlgorithm::Iterate(int granularity) {

  int n = state_->current_path_.size() - 1;

  if (n < 6) return false;

  if (granularity == 3) {

    if (enable_visuals_) {
      visualization_.clear();
    }

    int ath = current_search_first_edge_;

    // This way we don't chose nodes from the first edge.
    // Chose n-3 starting nodes, from the second node of the first edge.
    int cth = current_search_second_edge_;

    // Chose n-6 starting nodes, as every choice locks three edges
    int eth = current_search_third_edge_;

    int bth = ath + 1;
    int dth = cth + 1;
    int fth = eth + 1;

    int a = state_->current_path_[ath];
    int b = state_->current_path_[bth];
    int c = state_->current_path_[cth];
    int d = state_->current_path_[dth];
    int e = state_->current_path_[eth];
    int f = state_->current_path_[fth];


    double best_cost = GetCost(a, b, c, d, e, f);

    int best_variant = 0;
    double temp_cost;
    // revert b-c
    temp_cost = GetCost(a, c, b, d, e, f);
    if (DOUBLE_LESS(temp_cost, best_cost)) { best_variant = 0b001; best_cost = temp_cost; }
    // revert d-e
    temp_cost = GetCost(a, b, c, e, d, f);
    if (DOUBLE_LESS(temp_cost, best_cost)) { best_variant = 0b010; best_cost = temp_cost; }
    // revert f-a
    temp_cost = GetCost(f, b, c, d, e, a);
    if (DOUBLE_LESS(temp_cost, best_cost)) { best_variant = 0b100; best_cost = temp_cost; }
    // revert b-c, d-e
    temp_cost = GetCost(a, c, b, e, d, f);
    if (DOUBLE_LESS(temp_cost, best_cost)) { best_variant = 0b011; best_cost = temp_cost; }
    // revert d-e, f-a
    temp_cost = GetCost(f, b, c, e, d, a);
    if (DOUBLE_LESS(temp_cost, best_cost)) { best_variant = 0b110; best_cost = temp_cost; }
    // revert f-a, b-c
    temp_cost = GetCost(f, c, b, d, e, a);
    if (DOUBLE_LESS(temp_cost, best_cost)) { best_variant = 0b101; best_cost = temp_cost; }
    // revert b-c, d-e, f-a
    temp_cost = GetCost(f, c, b, e, d, a);
    if (DOUBLE_LESS(temp_cost, best_cost)) { best_variant = 0b111; best_cost = temp_cost; }

    if (best_variant & 0b001) {
      reverse(state_->current_path_.begin() + bth, state_->current_path_.begin() + cth + 1);
    }
    if (best_variant & 0b010) {
      reverse(state_->current_path_.begin() + dth, state_->current_path_.begin() + eth + 1);
    }
    if (best_variant & 0b100) {
      reverse(state_->current_path_.begin() + bth, state_->current_path_.begin() + eth + 1);
    }

    if (best_variant == 0) {
      PushVisualEdge({a,b, GlobalColor::green, 0.5});
      PushVisualEdge({c,d, GlobalColor::green, 0.5});
      PushVisualEdge({e,f, GlobalColor::green, 0.5});
    } else {
      PushVisualEdge({a,b, GlobalColor::red, 0.5});
      PushVisualEdge({c,d, GlobalColor::red, 0.5});
      PushVisualEdge({e,f, GlobalColor::red, 0.5});

      if (best_variant & 0b001) swap(b,c);
      if (best_variant & 0b010) swap(d,e);
      if (best_variant & 0b100) swap(f,a);

      PushVisualEdge({a,b, GlobalColor::green, 1.0});
      PushVisualEdge({c,d, GlobalColor::green, 1.0});
      PushVisualEdge({e,f, GlobalColor::green, 1.0});
    }

    if (best_variant != 0) {
      current_search_first_edge_ = 0;
      current_search_second_edge_ = 2;
      current_search_third_edge_ = 4;
    } else {
      current_search_third_edge_++;

      if (current_search_first_edge_ == 0) {
        if (current_search_third_edge_ == n-1) {
          current_search_second_edge_++;
          current_search_third_edge_ = current_search_second_edge_ + 2;
          if (current_search_third_edge_ >= n-1) {
            current_search_first_edge_ ++;
            current_search_second_edge_ = current_search_first_edge_ + 2;
            current_search_third_edge_ = current_search_second_edge_ + 2;
          }
        }
      } else {
        if (current_search_third_edge_ == n) {
          current_search_second_edge_++;
          current_search_third_edge_ = current_search_second_edge_ + 2;
          if (current_search_third_edge_ >= n) {
            current_search_first_edge_ ++;
            current_search_second_edge_ = current_search_first_edge_ + 2;
            current_search_third_edge_ = current_search_second_edge_ + 2;
            if (current_search_third_edge_ >= n) {
              return false;
            }
          }
        }
      }
    }

    return true;

  } else if (granularity == 2) {
    bool result = false;
    int last_second_edge = current_search_second_edge_;
    while (current_search_second_edge_ == last_second_edge) {
      result = Iterate(3);
      if (reset_) break;
      if (!result) break;
    }
    return result;
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

int Kopt3SearchImprovementAlgorithm::GetMaxGranularity() {
  return 3;
}

double Kopt3SearchImprovementAlgorithm::GetCost(int x1, int x2, int y1, int y2, int z1, int z2) {
  return (*state_->world_->distances_)[x1][x2] + (*state_->world_->distances_)[y1][y2] + (*state_->world_->distances_)[z1][z2];
}

} // namespace TSP
