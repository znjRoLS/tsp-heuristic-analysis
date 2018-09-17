#include "held_karp_lower_bound_algorithm.h"

#include <memory>
#include <map>
#include <limits>
#include "square_matrix.h"
#include "disjoint_set.h"
#include "double_compare.h"
#include "mst.h"
#include "vector_util.h"

using std::map;
using std::make_shared;
using std::numeric_limits;
using std::max;
using std::min;
using std::to_string;

namespace TSP {

HeldKarpLowerBoundAlgorithm::HeldKarpLowerBoundAlgorithm(int variant) :
    variant_(variant) {

}

void HeldKarpLowerBoundAlgorithm::Reset() {
  distances_ = make_shared<SquareMatrix<double>>(*(world_->distances_));

  curr_max_1tree_ = 0;
  current_node_ = 0;
  value_ = 0;

  step_data_.pi_ = vector<double>(world_->size, 0);
  step_data_.v_ = vector<int>(world_->size, 0);

  // set first step to minimum edge
  double min_edge = numeric_limits<double>::max();
  for (int i = 0 ; i < distances_->Size().first; i ++) {
      for (int j = 0 ; j < distances_->Size().second; j ++) {
          if (i == j) continue;
          min_edge = min(min_edge, (*distances_)[i][j]);
      }
  }
  step_data_.t_ = min_edge;
  step_data_.w_ = 0;

  step_data_.iter_no_increase_ = 0;
  step_data_.current_iter_ = 0;
  step_data_.current_period_ = world_->size / 2;
  step_data_.initial_increase_ = true;
}

bool HeldKarpLowerBoundAlgorithm::Iterate(int granularity) {

  int n = world_->size;

  if (granularity == 2) {

    if (variant_ == 1) {
      current_node_ = 0;
    }
    if (variant_ == 2) {
      double nearest_biggest = 0;

      for (int i = 0; i < n; i++) {
        pair<Edge, Edge> nearest_edges = MST::NearestNodesEdges(distances_, i);
        if (nearest_biggest < (*distances_)[nearest_edges.second.first][nearest_edges.second.second]) {
          nearest_biggest = (*distances_)[nearest_edges.second.first][nearest_edges.second.second];
          current_node_ = i;
        }
      }
    }

    auto min1tree = MST::Min1Tree(distances_, current_node_);

    visualization_.clear();
    for (auto& edge : min1tree) {
      if (edge.first == current_node_ || edge.second == current_node_) {
        visualization_.push_back({edge.first, edge.second, GlobalColor::green, 1.0});
      } else {
        visualization_.push_back({edge.first, edge.second, GlobalColor::green, 0.5});
      }
    }

    visual_params_["current_iter"] = to_string(step_data_.current_iter_);
    visual_params_["current_period"] = to_string(step_data_.current_period_);
    visual_params_["current_step_size"] = to_string(step_data_.t_);
    visual_params_["pi_"] = vector_to_string(step_data_.pi_);
    visual_params_["v_"] = vector_to_string(step_data_.v_);
    visual_params_["iter_no_increase"] = to_string(step_data_.iter_no_increase_);
    visual_params_["w"] = to_string(step_data_.w_);
    visual_params_["initial_increase"] = to_string(step_data_.initial_increase_);

    double total_weight = 0;
    for (auto &edge : min1tree) {
      total_weight += (*distances_)[edge.first][edge.second];
    }

    for (double pi_elem : step_data_.pi_) {
      total_weight -= pi_elem * 2;
    }

    if DOUBLE_GREATER(total_weight, value_) {
      value_ = total_weight;
    }

    if DOUBLE_GREATER(total_weight, curr_max_1tree_) {
      curr_max_1tree_ = total_weight;
      min_1tree_ = min1tree;
    }

    if (variant_ == 0) {

      current_node_++;

      if (current_node_ == n) {
        current_node_ = 0;

        bool res = IteratePi_0(min_1tree_, curr_max_1tree_);

        curr_max_1tree_ = 0;

        return res;
      }

      return true;
    }

    if (variant_ == 1 || variant_ == 2) {
      bool res;
      switch (variant_) {
        case 1:res = IteratePi_0(min_1tree_, curr_max_1tree_);
          break;
        case 2:res = IteratePi_2(min_1tree_, curr_max_1tree_);
          break;
      }
      curr_max_1tree_ = 0;
      return res;
    }

    if (variant_ == 3) {
      current_node_++;

      if (current_node_ == n) {
        current_node_ = 0;

        bool res = IteratePi_3(min_1tree_, curr_max_1tree_);

        curr_max_1tree_ = 0;

        return res;
      }
    }

  } else if (granularity == 1) {
    int last_current_iter = step_data_.current_iter_;
    int last_current_period = step_data_.current_period_;

    bool result = true;
    while (result && last_current_iter == step_data_.current_iter_ && last_current_period == step_data_.current_period_) {
      result = Iterate(2);
    }

    return result;
  } else if (granularity == 0) {
    while (Iterate(1));
    return false;
  }

  return true;
}

int HeldKarpLowerBoundAlgorithm::GetMaxGranularity() {
  return 2;
}

bool HeldKarpLowerBoundAlgorithm::IteratePi_0(unordered_set<pair<int, int>> min_1tree, double W) {
  int n = world_->size;

  bool w_increase = DOUBLE_GREATER(value_, step_data_.w_);
  step_data_.w_ = value_;

  vector<int> v(n, -2);

  for (auto &edge : min_1tree) {
    v[edge.first]++;
    v[edge.second]++;
  }

  // check if optimal tour (all zeros)
  bool all_zeroes = true;
  for (int v_single : v) {
    if (v_single != 0) all_zeroes = false;
  }

  if (all_zeroes) return false;

  if (step_data_.initial_increase_ && w_increase) {
    step_data_.t_ *= 2;
  } else {
    step_data_.initial_increase_ = false;
  }

  // check if period is zero
  if (step_data_.current_period_ == step_data_.current_iter_) {
    if (w_increase) {
      step_data_.current_period_ *= 2;
    } else {
      step_data_.current_period_ /= 2;
      step_data_.t_ /= 2;

      step_data_.current_iter_ = 0;
      if (step_data_.current_period_ == 0) {
        return false;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    double pi_change = step_data_.t_ * v[i];
    step_data_.pi_[i] += pi_change;
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      (*distances_)[i][j] += pi_change;
      (*distances_)[j][i] += pi_change;
    }
  }

  step_data_.v_ = v;

  step_data_.current_iter_++;
  return true;
}

bool HeldKarpLowerBoundAlgorithm::IteratePi_2(unordered_set<pair<int, int>> min_1tree, double W) {
  int n = world_->size;

  bool w_increase = DOUBLE_GREATER(value_, step_data_.w_);
  step_data_.w_ = value_;

  vector<int> v(n, -2);

  for (auto &edge : min_1tree) {
    v[edge.first]++;
    v[edge.second]++;
  }

  // check if optimal tour (all zeros)
  bool all_zeroes = true;
  for (int v_single : v) {
    if (v_single != 0) all_zeroes = false;
  }

  if (all_zeroes) return false;

  if (step_data_.initial_increase_ && w_increase) {
    step_data_.t_ *= 2;
  } else {
    step_data_.initial_increase_ = false;
  }

  // check if period is zero
  if (step_data_.current_period_ == step_data_.current_iter_) {
    if (w_increase) {
      step_data_.current_period_ *= 2;
    } else {
      step_data_.current_period_ /= 2;
      step_data_.t_ /= 2;

      step_data_.current_iter_ = 0;
      if (step_data_.current_period_ == 0) {
        return false;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    double
        pi_change = step_data_.t_ * (step_data_.v_[i] * step_data_.v_intertia_ + v[i] * (1 - step_data_.v_intertia_));
    step_data_.pi_[i] += pi_change;
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      (*distances_)[i][j] += pi_change;
      (*distances_)[j][i] += pi_change;
    }
  }

  step_data_.v_ = v;

  step_data_.current_iter_++;
  return true;
}

bool HeldKarpLowerBoundAlgorithm::IteratePi_3(unordered_set<pair<int, int>> min_1tree, double W) {
  int n = world_->size;

  bool w_increase = DOUBLE_GREATER(W, step_data_.w_);
  step_data_.w_ = W;

  vector<int> v(n, -2);

  for (auto &edge : min_1tree) {
    v[edge.first]++;
    v[edge.second]++;
  }

  // check if optimal tour (all zeros)
  bool all_zeroes = true;
  for (int v_single : v) {
    if (v_single != 0) all_zeroes = false;
  }

  if (all_zeroes) return false;

  if (w_increase) {
    step_data_.iter_no_increase_ = 0;
    step_data_.t_ *= 2;
  } else {
    step_data_.t_ /= 2;
    step_data_.iter_no_increase_++;
    if (step_data_.iter_no_increase_ == 10) {
      return false;
    }
  }

  for (int i = 0; i < n; i++) {
    double
        pi_change = step_data_.t_ * (step_data_.v_[i] * step_data_.v_intertia_ + v[i] * (1 - step_data_.v_intertia_));
    step_data_.pi_[i] += pi_change;
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      (*distances_)[i][j] += pi_change;
      (*distances_)[j][i] += pi_change;
    }
  }

  step_data_.v_ = v;

  step_data_.current_iter_++;
  return true;
}

}; // namespace TSP
