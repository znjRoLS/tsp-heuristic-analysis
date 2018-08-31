//
// Created by Bojan Roško on 9/2/17.
//

#include "Algorithms.h"

#include <algorithm>
#include <limits>
#include <cmath>

namespace TSP{

  unordered_map<string, Algorithm*> algorithm_container;

  void AlgorithmBruteForce::Setup(SharedState arg_state) {
    state = arg_state;
    state->current_path = State::Default(state->world->size());
  }

  bool AlgorithmBruteForce::Iterate() {

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

    for (unsigned i = 1; i < arg_state->world->size(); i++) {
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


  AlgorithmAntColonyOptimization::AlgorithmAntColonyOptimization():
      matrix(new vector<vector<double>>) {

  }

  void AlgorithmAntColonyOptimization::SetSettings(Settings arg_settings) {
    settings = arg_settings;
  }

  void AlgorithmAntColonyOptimization::Setup(SharedState arg_state) {
    state = arg_state;
    for (unsigned i = 0; i < state->world->size(); i ++) {
      matrix->push_back({});
      for (unsigned j = 0; j < state->world->size(); j++) {
        matrix->at(i).push_back(1);
      }
    }

    state->current_path_ant_colony = matrix;
  }

  bool AlgorithmAntColonyOptimization::Iterate() {

    ants.clear();
    for (int ai = 0; ai < settings.num_ants; ai++) {
      ants.push_back({});
      ants[ai].path = make_shared<vector<int>>();
      ants[ai].path->push_back(0);
      for (unsigned i = 0 ; i < state->world->size(); i++) {
        ants[ai].unvisited.insert(i);
      }
    }

    for (unsigned i = 0 ; i < state->world->size(); i ++) {
      SubIterate();
    }

    UpdateTrails();

    return true;
  }

  void AlgorithmAntColonyOptimization::SubIterate() {
    for (int ai = 0; ai < settings.num_ants; ai ++) {
      AntIterate(ants[ai]);
    }
  }

  void AlgorithmAntColonyOptimization::AntIterate(Ant& ant) {
    vector<double> weights;
    vector<int> nodes;

    for (const int& node : ant.unvisited) {
      nodes.push_back(node);
      int curr_position = *ant.path->rbegin();
      double weight = pow(1.0/GetCost(state->world, curr_position, node), settings.alpha);
      weight += pow(matrix->at(curr_position)[node], settings.eta);
      weights.push_back(weight);
    }

    int chosen_next = WeightedRandom(weights, nodes);

    ant.path->push_back(chosen_next);
    ant.unvisited.erase(chosen_next);
  }

  void AlgorithmAntColonyOptimization::UpdateTrails() {
    for (unsigned i = 0; i < matrix->size(); i ++) {
      for (unsigned j = 0; j < matrix->at(i).size(); j++) {
        matrix->at(i)[j] += settings.ro;
      }
    }

    for (unsigned ai = 0; ai < ants.size(); ai ++) {

      double cost = GetCost(state->world, ants[ai].path);

      for (unsigned i = 1; i < ants[ai].path->size(); i ++) {
        matrix->at(ants[ai].path->at(i-1))[ants[ai].path->at(i)] += settings.Q/cost;
      }
    }
  }


  REGISTER_ALGORITHM(AlgorithmAntColonyOptimization);
}
