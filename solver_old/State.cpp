//
// Created by Bojan Roško on 9/4/17.
//

#include "State.h"
#include <sstream>

namespace TSP {

  State::State(World arg_world) :
      world(arg_world),
      optimal_path(State::Default(arg_world->size())) {
  }

  Path State::Default(int size) {
    Path default_state(new vector<int>());
    for (int i = 0; i < size; i++) {
      default_state->push_back(i);
    }

    return default_state;
  }

  string State::ToString() {
    stringstream ss;
    if (world != nullptr) {
      ss << "World: ";
      for (auto point: (*world)) {
        ss << point << " ";
      }
      ss << endl;
    }
    if (optimal_path != nullptr) {
      ss << "Current optimal path: ";
      for (auto node: (*optimal_path)){
        ss << node << " ";
      }
      ss << endl;
    }
    if (current_path != nullptr) {
      ss << "Current path: ";
      for (auto node: (*current_path)){
        ss << node << " ";
      }
      ss << endl;
    }
    return ss.str();
  }
}

ostream& operator<<(ostream& out, const TSP::SharedState& state) {
  if (state->world != nullptr) {
    out << "World: ";
    for (auto point: (*state->world)) {
      out << point << " ";
    }
    out << endl;
  }
  if (state->optimal_path != nullptr) {
    out << "Current optimal path: ";
    for (auto node: (*state->optimal_path)){
      out << node << " ";
    }
    out << endl;
  }
  if (state->current_path != nullptr) {
    out << "Current path: ";
    for (auto node: (*state->current_path)){
      out << node << " ";
    }
    out << endl;
  }

  return out;
}