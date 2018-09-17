#include "held_karp_lower_bound_algorithm.h"

#include <memory>
#include <map>
#include <limits>
#include "square_matrix.h"
#include "disjoint_set.h"
#include "double_compare.h"
#include "mst.h"

using std::map;
using std::make_shared;
using std::numeric_limits;
using std::max;

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

  // set first step to maximum edge
  double max_edge = 0;
  for (auto &row : world_->distances_->GetData())
    for (auto &dist : row) {
      max_edge = max(max_edge, dist);
    }
  step_data_.t_ = max_edge;
  step_data_.w_ = 0;

  step_data_.iter_no_increase_ = 0;
  step_data_.current_iter_ = 0;
  step_data_.current_period_ = world_->size / 2;
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

    double total_weight = 0;
    for (auto &edge : min1tree) {
      total_weight += (*world_->distances_)[edge.first][edge.second];
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
    bool result;
    do {
      result = Iterate(2);
    } while (current_node_ != 0);

    return result;
  } else if (granularity == 0) {
    while (Iterate(1));
    return false;
  }

  return true;
}

int HeldKarpLowerBoundAlgorithm::GetMaxGranularity() {
  return 0;
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
