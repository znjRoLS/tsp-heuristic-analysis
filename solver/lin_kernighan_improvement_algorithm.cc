#include "lin_kernighan_improvement_algorithm.h"

#include "alfa_measure.h"
#include <algorithm>
#include "random.h"
#include "container_contains.h"
#include "double_compare.h"

using std::sort;
using std::max;
using std::swap;

namespace TSP {

LinKernighanImprovementAlgorithm::LinKernighanImprovementAlgorithm(int variant):
variant_(variant), metric_initialized_(false) {

}

void LinKernighanImprovementAlgorithm::Reset() {
  metric_initialized_ = false;
  sorted_edges_.clear();
  current_check_edge = 0;

  check_order_.clear();
  for (int i = 0 ; i < state_->world_->size; i ++) {
    check_order_.push_back({i, 1});
    check_order_.push_back({i, -1});
  }

  Random::Shuffle(check_order_.begin(), check_order_.end());

  g.clear();
  G.clear();

  current_tour_edges_= vector<pair<int,int>>(state_->world_->size);

  int last_node = state_->current_path_[0];
  for (unsigned i = 1 ; i < state_->current_path_.size(); i ++) {
    int next_node = state_->current_path_[i];
    current_tour_edges_[last_node].second = next_node;
    current_tour_edges_[next_node].first = last_node;
    last_node = next_node;
  }

  curr_t = vector<int>(state_->world_->size + 10, 0);

  current_t_.clear();
}

bool LinKernighanImprovementAlgorithm::Iterate(int granularity) {
  int n = state_->world_->size;

  const shared_ptr<SquareMatrix<double>>& dist = state_->world_->distances_;

  if (granularity == 2) {

    if (!metric_initialized_) {
      metric_initialized_ = true;
      switch (variant_) {
        case 0:
          optimization_metric_ = state_->world_->distances_;
          break;
        case 1:
          optimization_metric_ = AlfaMeasure(state_->world_->distances_);
          break;
        case 2:
          optimization_metric_ = AlfaImprovedMeasure(state_->world_->distances_);
          break;
      }

      sorted_edges_ = vector<vector<int>>(n);
      for (int i = 0 ; i < n ; i ++) {
        for (int j = 0 ; j < n; j ++) {
          if (i == j) continue;
          sorted_edges_[i].push_back(j);
        }
        sort(sorted_edges_[i].begin(), sorted_edges_[i].end(), [&](const auto& lhs, const auto& rhs) {
            return (*optimization_metric_)[i][lhs] < (*optimization_metric_)[i][rhs];
        });
      }

      if(enable_visuals_) {
        visualization_.clear();
      }


      double max_edge = 0;
      for (int i = 0 ; i < n; i ++) {
        for (int j = i + 1; j < n; j++) {
          max_edge = max(max_edge, (*optimization_metric_)[i][j]);
        }
      }

      double max_scale = 0;
      for (int i = 0 ; i < n; i ++) {
        for (int j = i + 1; j < n; j++) {
          max_scale = max(max_scale, 1/max(0.05, (*optimization_metric_)[i][j]/max_edge));
        }
      }


      for (int i = 0 ; i < n; i ++) {
        for (int j = i + 1; j < n ; j ++) {
          PushVisualEdge({i, j, GlobalColor::darkGray, 1/max(0.05, (*optimization_metric_)[i][j]/max_edge)/max_scale});
        }
      }


      for (int i = 0 ; i < n; i ++) {
        for (int j = i + 1; j < n; j++) {
          if ((*optimization_metric_)[i][j] < 0.0001) PushVisualEdge({i, j, GlobalColor::darkGray, 1.0});
        }
      }

      return true;
    }

    if (enable_visuals_) {
      while(!visualization_.empty() && visualization_.rbegin()->color != GlobalColor::darkGray && visualization_.rbegin()->color != GlobalColor::green) {
        visualization_.pop_back();
      }
      if (!visualization_.empty() && visualization_.rbegin()->color == GlobalColor::green ) {
        visualization_.rbegin()->color = GlobalColor ::darkGray;
      }
    }


    if (current_t_.empty()) {

      if (enable_visuals_) {
        visualization_.clear();
      }

      // end!
      if (static_cast<unsigned>(current_check_edge) == check_order_.size()) {
        return false;
      }

      auto& par = check_order_[current_check_edge];
      current_check_edge ++;

      int t1 = state_->current_path_[par.first];
      int t2 = state_->current_path_[(par.first + par.second + n)%n]; // second is 1 or -1, meaning node before or after.
      current_t_.push_back(t1);
      current_t_.push_back(t2);
      PushVisualEdge({t1, t2, GlobalColor::darkGray, 0.7});

      curr_t3 = 0;

    } else if (current_t_.size() == 2) {

      int t1 = current_t_[0];
      int t2 = current_t_[1];
      if (static_cast<unsigned>(curr_t3) == sorted_edges_[t2].size()) {
        current_t_.clear();
        return true;
      }

      int potential_t3 = sorted_edges_[t2][curr_t3];

      if (AlreadyChosen(potential_t3)) {
        PushVisualEdge({t2, potential_t3, GlobalColor::blue, 0.7});
      } else if (current_tour_edges_[t2].first == potential_t3 || current_tour_edges_[t2].second == potential_t3) {
        PushVisualEdge({t2, potential_t3, GlobalColor::blue, 0.7});
      } else if ((*dist)[t2][potential_t3] > (*dist)[t1][t2]) {
        PushVisualEdge({t2, potential_t3, GlobalColor::red, 0.7});
      } else {
        PushVisualEdge({t2, potential_t3, GlobalColor::green, 0.7});
        current_t_.push_back(potential_t3);
        curr_t4 = 0;
      }

      curr_t3 ++;
      return true;

    } else if (current_t_.size() == 3) {

//      int t1 = current_t_[0];
//      int t2 = current_t_[1];
      int t3 = current_t_[2];

      if (curr_t4 == 2) {
        current_t_.pop_back();
        if (enable_visuals_) {
          visualization_.pop_back();
        }
        return true;
      }

      int potential_t4 = 0;
      if (curr_t4 == 0) {
        potential_t4 = current_tour_edges_[t3].first;
      } else if (curr_t4 == 1) {
        potential_t4 = current_tour_edges_[t3].second;
      }

      if (AlreadyChosen(potential_t4)) {
        PushVisualEdge({t3, potential_t4, GlobalColor::blue, 0.7});
      } else {
        current_t_.push_back(potential_t4);
        if (CheckValidTour()) {
          if (PositiveGain()) {
            PushVisualEdge({t3, potential_t4, GlobalColor::darkGreen, 0.7});

            UpdateTour();

          } else {
            curr_t5 = 0;
            PushVisualEdge({t3, potential_t4, GlobalColor::green, 0.7});
          }
        } else {
          PushVisualEdge({t3, potential_t4, GlobalColor::red, 0.7});
          current_t_.pop_back();
        }
      }

      curr_t4++;
      return true;
    } else if (current_t_.size() == 4) {

//      int t1 = current_t_[0];
//      int t2 = current_t_[1];
//      int t3 = current_t_[2];
      int t4 = current_t_[3];
      if (static_cast<unsigned>(curr_t5) == sorted_edges_[t4].size()) {
        current_t_.pop_back();
        if (enable_visuals_) {
          visualization_.pop_back();
        }
        return true;
      }

      int potential_t5 = sorted_edges_[t4][curr_t5];

      if (AlreadyChosen(potential_t5)) {
        PushVisualEdge({t4, potential_t5, GlobalColor::blue, 0.7});
      } else if (current_tour_edges_[t4].first == potential_t5 || current_tour_edges_[t4].second == potential_t5) {
        PushVisualEdge({t4, potential_t5, GlobalColor::blue, 0.7});
      } else {

        current_t_.push_back(potential_t5);
        if (CheckPositiveGain()) {
          PushVisualEdge({t4, potential_t5, GlobalColor::green, 0.7});

          curr_t[6] = 0;
        } else {
          PushVisualEdge({t4, potential_t5, GlobalColor::red, 0.7});
          current_t_.pop_back();
        }

      }

      curr_t5 ++;
      return true;
    } else if (current_t_.size() % 2 == 1) {

      int last_t = *current_t_.rbegin();
      if (curr_t[current_t_.size() + 1] == 2) {
        current_t_.pop_back();
        if (enable_visuals_) {
          visualization_.pop_back();
        }
        return true;
      }

      int potential_t = 0;
      if (curr_t[current_t_.size() + 1] == 0) {
        potential_t = current_tour_edges_[last_t].first;
      } else if (curr_t[current_t_.size() + 1] == 1) {
        potential_t = current_tour_edges_[last_t].second;
      }

      curr_t[current_t_.size() + 1] ++;

      if (AlreadyChosen(potential_t)) {
        PushVisualEdge({last_t, potential_t, GlobalColor::blue, 0.7});
      } else {
        current_t_.push_back(potential_t);
        if (CheckValidTour()) {
          if (PositiveGain()) {
            PushVisualEdge({last_t, potential_t, GlobalColor::darkGreen, 0.7});

            UpdateTour();

          } else {
            // its for the next one
            curr_t[current_t_.size() + 1] = 0;
            PushVisualEdge({last_t, potential_t, GlobalColor::green, 0.7});
          }
        } else {
          PushVisualEdge({last_t, potential_t, GlobalColor::red, 0.7});
          current_t_.pop_back();
        }
      }

      return true;

    } else if (current_t_.size() % 2 == 0) {

      int last_t = *current_t_.rbegin();
      if (curr_t[current_t_.size() + 1] == try_nearest_) {
        current_t_.pop_back();
        if (enable_visuals_) {
          visualization_.pop_back();
        }
        return true;
      }

      int potential_t = sorted_edges_[last_t][curr_t[current_t_.size() + 1]];

      curr_t[current_t_.size() + 1] ++;

      if (AlreadyChosen(potential_t)) {
        PushVisualEdge({last_t, potential_t, GlobalColor::blue, 0.7});
      } else if (current_tour_edges_[last_t].first == potential_t || current_tour_edges_[last_t].second == potential_t) {
        PushVisualEdge({last_t, potential_t, GlobalColor::blue, 0.7});
      } else {

        current_t_.push_back(potential_t);
        if (CheckPositiveGain()) {
          PushVisualEdge({last_t, potential_t, GlobalColor::green, 0.7});

          curr_t[current_t_.size() + 1] = 0;

        } else {
          PushVisualEdge({last_t, potential_t, GlobalColor::red, 0.7});
          current_t_.pop_back();
        }

      }
    }

  } else if (granularity == 1) {

    bool res = true;
    do {
      res = Iterate(2);
    } while (res && current_check_edge != 0);

    return res;
  } else if (granularity == 0) {
    while(Iterate(1));
    return  false;
  }

  return true;
}

int LinKernighanImprovementAlgorithm::GetMaxGranularity() {
  return 2;
}

bool LinKernighanImprovementAlgorithm::CheckValidTour() {
  TSP_ASSERT(current_t_.size()%2 == 0);

  int n = state_->world_->size;

  unordered_map<int,int> xs;
  unordered_map<int,int> ys;


  for (unsigned i = 0 ; i + 1 < current_t_.size(); i ++) {
    if (i%2 == 0) {
      xs.insert({current_t_[i], current_t_[i+1]});
      xs.insert({current_t_[i+1], current_t_[i]});
    } else {
      ys.insert({current_t_[i], current_t_[i+1]});
      ys.insert({current_t_[i+1], current_t_[i]});
    }
  }
  ys.insert({current_t_[0], *current_t_.rbegin()});
  ys.insert({*current_t_.rbegin(), current_t_[0]});

  int num_visited = 0;
  vector<bool> visited(n, false);
  int curr_node = 0;
  visited[curr_node] = true;

  if (CONTAINS(xs, 0)) {
    TSP_ASSERT(CONTAINS(ys, 0));
    curr_node = ys[0];
  } else {
    curr_node = current_tour_edges_[0].first;
  }
  visited[curr_node] = true;
  num_visited ++;

  while (curr_node != 0) {
    if (!visited[current_tour_edges_[curr_node].first] && !(CONTAINS(xs, curr_node) && xs[curr_node] == current_tour_edges_[curr_node].first )) {
      curr_node = current_tour_edges_[curr_node].first;
    } else if (!visited[current_tour_edges_[curr_node].second] && !(CONTAINS(xs, curr_node) && xs[curr_node] == current_tour_edges_[curr_node].second )) {
      curr_node = current_tour_edges_[curr_node].second;
    } else if (CONTAINS(ys, curr_node) && !visited[ys[curr_node]] ) {
      curr_node = ys[curr_node];
    } else {
      curr_node = 0;
    }

    visited[curr_node] = true;
    num_visited ++;
  }

  return num_visited == n;
}

bool LinKernighanImprovementAlgorithm::PositiveGain() {
  TSP_ASSERT(current_t_.size()%2 == 0);

  double sum = 0;
  for (unsigned i = 0 ; i + 1 < current_t_.size(); i ++) {
    if (i % 2 == 0) {
      sum -= (*state_->world_->distances_)[current_t_[i]][current_t_[i+1]];
    } else {
      sum += (*state_->world_->distances_)[current_t_[i]][current_t_[i+1]];
    }
  }

  int t1 = current_t_[0];
  int tn = (*current_t_.rbegin());
  sum += (*state_->world_->distances_)[tn][t1];

  return DOUBLE_LESS(sum, 0);
}

bool LinKernighanImprovementAlgorithm::CheckPositiveGain() {
  TSP_ASSERT(current_t_.size()%2 == 1);

  double sum = 0;
  for (unsigned i = 0 ; i + 1 < current_t_.size(); i ++) {
    if (i % 2 == 0) {
      sum -= (*state_->world_->distances_)[current_t_[i]][current_t_[i+1]];
    } else {
      sum += (*state_->world_->distances_)[current_t_[i]][current_t_[i+1]];
    }
  }

  return DOUBLE_LESS(sum, 0);
}

void LinKernighanImprovementAlgorithm::UpdateTour() {
  int n = state_->world_->size;

  if (enable_visuals_) {
    visualization_.clear();
  }
  int vis_last_node = current_t_[0];
  for (unsigned i = 1; i < current_t_.size(); i ++) {
    int next_node = current_t_[i];
    if (i % 2 == 1) {
      PushVisualEdge({vis_last_node, next_node, GlobalColor::red, 1.0});
    } else {
      PushVisualEdge({vis_last_node, next_node, GlobalColor::green, 1.0});
    }
    vis_last_node = next_node;
  }
  PushVisualEdge({vis_last_node, current_t_[0], GlobalColor::green, 1.0});

  unordered_map<int,int> xs;
  unordered_map<int,int> ys;


  for (unsigned i = 0 ; i + 1 < current_t_.size(); i ++) {
    if (i%2 == 0) {
      xs.insert({current_t_[i], current_t_[i+1]});
      xs.insert({current_t_[i+1], current_t_[i]});
    } else {
      ys.insert({current_t_[i], current_t_[i+1]});
      ys.insert({current_t_[i+1], current_t_[i]});
    }
  }
  ys.insert({current_t_[0], *current_t_.rbegin()});
  ys.insert({*current_t_.rbegin(), current_t_[0]});


  for (int i = 0 ; i < n; i ++) {
    if (CONTAINS(xs, i)) {
      if (xs[i] == current_tour_edges_[i].first) {
        current_tour_edges_[i].first = ys[i];
      } else if (xs[i] == current_tour_edges_[i].second) {
        current_tour_edges_[i].second = ys[i];
      }
    }
  }

  int last_node = 0;
  for (int i = 1; i < n ; i ++ ) {
    int next_node = current_tour_edges_[last_node].second;
    if (last_node == current_tour_edges_[next_node].second) {
      swap(current_tour_edges_[next_node].first, current_tour_edges_[next_node].second);
    }

    state_->current_path_[i] = next_node;

    last_node = next_node;
  }

  TSP_ASSERT_EQ(current_tour_edges_[last_node].second, 0);


  current_t_.clear();
  current_check_edge = 0;
  Random::Shuffle(check_order_.begin(), check_order_.end());
}

bool LinKernighanImprovementAlgorithm::AlreadyChosen(int t) {
  for (auto t_ : current_t_) {
    if (t_ == t) {
      return true;
    }
  }

  return false;
}

} // namespace TSP
