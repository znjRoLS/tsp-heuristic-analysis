//
// Created by Bojan Roško on 9/2/17.
//

#include "Algorithms.h"

#include <algorithm>

namespace TSP{

  void AlgorithmBruteForce::Setup(SharedState arg_state) {
    state = arg_state;
  }

  bool AlgorithmBruteForce::Iterate() {
    if (state->path == nullptr) {
      state->path = Path(new vector<int>());
      for (int i = 0; i < state->world->size(); i++) {
        state->path->push_back(i);
      }
      return true;
    } else {
      return next_permutation(state->path->begin(), state->path->end());
    }
  }
}
