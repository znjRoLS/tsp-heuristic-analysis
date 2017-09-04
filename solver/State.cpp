//
// Created by Bojan Roško on 9/4/17.
//

#include "State.h"

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