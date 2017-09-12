//
// Created by Bojan Roško on 9/2/17.
//

#include "Algorithms.h"

#include <algorithm>
#include <limits>

namespace TSP{

  unordered_map<string, Algorithm*> algorithm_container;

  void AlgorithmBruteForce::Setup(SharedState arg_state) {
    state = arg_state;
  }

  bool AlgorithmBruteForce::Iterate() {
    if (state->current_path == nullptr) {
      state->current_path = State::Default(state->world->size());
    }
    if (!next_permutation(state->current_path->begin(), state->current_path->end())) {
      return false;
    } else {
      SetMin(state->world, state->optimal_path, state->current_path);
      return true;
    }
  }

  REGISTER_ALGORITHM(AlgorithmBruteForce);


  void AlgorithmNearestNeighbour::Setup(SharedState arg_state) {
    state = arg_state;

    for (int i = 1; i < arg_state->world->size(); i++) {
      unvisited.insert(i);
    }
    state->current_path = {0};
  }

  bool AlgorithmNearestNeighbour::Iterate() {
    int min_ind;
    double min_val = numeric_limits<double>::max();

    if (unvisited.empty()) {
      return false;
    }

    for (const int& unvisited_node : unvisited) {
      double cost = GetCost(state->world, state->current_path->at(state->current_path->size()), unvisited_node);
      if (min_val > cost) {
        min_ind = unvisited_node;
        min_val = cost;
      }
    }
    unvisited.erase(min_ind);
    state->current_path->push_back(min_ind);

    return true;
  }


  REGISTER_ALGORITHM(AlgorithmNearestNeighbour);
}
