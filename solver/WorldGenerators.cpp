//
// Created by Bojan Roško on 9/2/17.
//

#include "WorldGenerators.h"

namespace TSP {

  unordered_map<string, WorldGenerator*> world_generator_container;

  World WorldGeneratorRandom::GenerateWorld(int size) {

    shared_ptr<vector<pair<double, double>>> world(new vector<pair<double, double>>());
    for (int i = 0; i < size; i++) {
      world->push_back(make_pair<double, double>(Random(), Random()));
    }
    return move(world);
  }

  REGISTER_WORLD_GENERATOR(WorldGeneratorRandom);
}