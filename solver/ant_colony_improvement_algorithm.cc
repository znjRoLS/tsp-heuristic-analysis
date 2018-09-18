#include "ant_colony_improvement_algorithm.h"

#include <memory>
#include <cmath>
#include "random.h"
#include <limits>

using std::make_shared;
using std::max;
using std::to_string;
using std::numeric_limits;


namespace TSP {

AntColonyImprovementAlgorithm::AntColonyImprovementAlgorithm(int variant, int num_ants, double alfa, double beta, double ro, double q, double phi) :
    variant_(variant), num_ants_(num_ants), alfa_(alfa), beta_(beta), ro_(ro), q_(q), phi_(phi) {

}

void AntColonyImprovementAlgorithm::Reset() {

  int n = state_->world_->size;

  ants_ = vector<Ant> (num_ants_);

  pheromones_ = make_shared<SquareMatrix<double>>(n);

  for (int i = 0 ; i < n; i ++) {
    for (int j = 0 ; j < n ; j ++) {
      (*pheromones_)[i][j] = phi_;
    }
  }

  current_ant_ = 0;
}

bool AntColonyImprovementAlgorithm::Iterate(int granularity) {
  if (granularity == 2) {
    // one decision of one ant

    if (current_ant_ == num_ants_) {
      if (current_cost_ant_ == num_ants_) {

        current_ant_ = 0;

        double new_cost = State::PathCost(ants_[current_best_ant_].current_path_, state_->world_->distances_);
        if (new_cost < state_->CurrentPathCost()) {
          state_->current_path_ = ants_[current_best_ant_].current_path_;
        }

        UpdatePheromones();

        current_ant_ = 0;
        ants_ = vector<Ant> (num_ants_);


      } else {
        double new_cost = State::PathCost(ants_[current_cost_ant_].current_path_, state_->world_->distances_);
        if (new_cost < current_best_ant_cost_) {
          current_best_ant_cost_ = new_cost;
          current_best_ant_ = current_cost_ant_;
        }

        visual_params_["current_ant_path_cost"] = to_string(new_cost);

        visualization_.clear();

        auto& path = ants_[current_cost_ant_].current_path_;
        int last = path[0];
        for (unsigned i = 0 ; i < path.size(); i ++) {
          int next = path[i];

          visualization_.push_back({last, next, GlobalColor::green, 0.5});

          last = next;
        }

        path = ants_[current_cost_ant_].current_path_;
        last = path[0];
        for (unsigned i = 0 ; i < path.size(); i ++) {
          int next = path[i];

          visualization_.push_back({last, next, GlobalColor::darkGreen, 0.5});

          last = next;
        }

        current_cost_ant_++;
      }

      return true;

    }

    if (ants_[current_ant_].current_path_.empty()) {
      visualization_.clear();
      for (int i = 1; i < state_->world_->size; i++) {
        ants_[current_ant_].unvisited_.insert(i);
      }
      ants_[current_ant_].current_path_.push_back(0);
    }

    int ant_next_node = AntChosePath(ants_[current_ant_], pheromones_, state_->world_->distances_);
    ants_[current_ant_].unvisited_.erase(ant_next_node);
    ants_[current_ant_].current_path_.push_back(ant_next_node);

    visualization_.push_back({(*(ants_[current_ant_].current_path_.rbegin() + 1)),
                              ((*ants_[current_ant_].current_path_.rbegin())), GlobalColor::green, 0.5});

    // end of iterate(1) or iterate(0);
    if (ants_[current_ant_].unvisited_.empty()) {
      ants_[current_ant_].current_path_.push_back(0);
      visualization_.push_back({(*(ants_[current_ant_].current_path_.rbegin() + 1)),
                                (*(ants_[current_ant_].current_path_.rbegin())), GlobalColor::green, 0.5});

      current_ant_++;
      if (current_ant_ == num_ants_) {
        current_cost_ant_ = 0;
        current_best_ant_ = -1;
        current_best_ant_cost_ = numeric_limits<double>::max();
      }
    }

    return true;

  } else if (granularity == 1) {
    // single ant
    int last_current_ant = current_ant_;
    bool result = true;
    while (result && current_ant_ == last_current_ant) {
      result = Iterate(2);
    }

    return result;

  } else if (granularity == 0) {
    // whole ants update
    bool result = true;
    do {
      result = Iterate(1);
    } while (result && current_ant_ != 0);

    return result;
  }

  return true;
}

int AntColonyImprovementAlgorithm::GetMaxGranularity() {
  return 2;
}

int AntColonyImprovementAlgorithm::AntChosePath(const Ant &ant,
                                                const shared_ptr<SquareMatrix<double>> &pheromones,
                                                const shared_ptr<SquareMatrix<double>> &distances) {

  int n = distances->Size().first;
  vector<double> weights(n, 0.0);

  int current_node = *ant.current_path_.rbegin();
  for (auto &node : ant.unvisited_) {
    double tau = (*pheromones)[current_node][node];
    double eta = 1.0/(*distances)[current_node][node];
    weights[node] = pow(tau, alfa_) * pow(eta, beta_);
  }

  return Random::GetWeightedInt(weights);
}

void AntColonyImprovementAlgorithm::UpdatePheromones() {
  int n = pheromones_->Size().first;

  for (int i = 0 ; i < n; i ++) {
    for (int j = 0 ; j < n ; j ++) {
      (*pheromones_)[i][j] *= 1-ro_;
    }
  }

  if (variant_ == 0) {
    auto& ant = ants_[current_best_ant_];

    double ant_path_cost = State::PathCost(ant.current_path_, state_->world_->distances_);
//  double increment = state_->CurrentPathCost() / ant_path_cost;
    double increment = q_ / ant_path_cost;

    int last = ant.current_path_[0];
    for (unsigned i = 1 ; i < ant.current_path_.size(); i ++) {
      int next = ant.current_path_[i];
      (*pheromones_)[last][next] += increment;
      (*pheromones_)[next][last] += increment;
      last = next;
    }
  } else if (variant_ == 1) {
    for (auto& ant : ants_) {
      double ant_path_cost = State::PathCost(ant.current_path_, state_->world_->distances_);
//  double increment = state_->CurrentPathCost() / ant_path_cost;
      double increment = q_ / ant_path_cost;

      int last = ant.current_path_[0];
      for (unsigned i = 1 ; i < ant.current_path_.size(); i ++) {
        int next = ant.current_path_[i];
        (*pheromones_)[last][next] += increment;
        (*pheromones_)[next][last] += increment;
        last = next;
      }
    }
  }

  visualization_.clear();

  double max_pheromone = 0.0;
  for (int i = 0 ; i < n; i ++) {
    for (int j = 0 ; j < n ; j ++) {
      max_pheromone = max(max_pheromone, (*pheromones_)[i][j]);
    }
  }

  for (int i = 0 ; i < n; i ++) {
    for (int j = i+1; j < n; j++) {

      visualization_.push_back({i, j, GlobalColor::darkGray, (*pheromones_)[i][j]/max_pheromone});

    }
  }
}

};// namespace TSP
