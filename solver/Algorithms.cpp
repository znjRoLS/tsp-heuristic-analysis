//
// Created by Bojan Roško on 9/2/17.
//

#include "Algorithms.h"

#include <algorithm>

namespace TSP{

  unordered_map<string, Algorithm*> algorithm_container;

  void AlgorithmBruteForce::Setup(SharedState arg_state) {
    state = arg_state;
    current_path = State::Default(arg_state->world->size());

  }

  bool AlgorithmBruteForce::Iterate() {
    if (!next_permutation(current_path->begin(), current_path->end())) {
      return false;
    } else {
      SetMin(state->world, state->path, current_path);
      return true;
    }
  }


  REGISTER_ALGORITHM(AlgorithmBruteForce);
}
