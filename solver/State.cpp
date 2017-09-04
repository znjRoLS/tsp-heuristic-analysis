//
// Created by Bojan Roško on 9/4/17.
//

#include "State.h"

TSP::State::State(World arg_world):
    world(arg_world),
    path(Default(arg_world->size())){
}

Path TSP::State::Default(int size) {
  Path default_state(new vector<int>());
  for (int i = 0; i < size; i++) {
    default_state->push_back(i);
  }

  return default_state;
}

ostream& operator<<(ostream& out, const TSP::SharedState& state) {
  if (state->world != nullptr) {
    cout << "World: ";
    for (auto point: (*state->world)) {
      cout << point << " ";
    }
    cout << endl;
  }
  if (state->path != nullptr) {
    cout << "Path: ";
    for (auto node: (*state->path)){
      cout << node << " ";
    }
    cout << endl;
  }

  return out;
}