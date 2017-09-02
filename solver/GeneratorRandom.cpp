//
// Created by Bojan Roško on 9/2/17.
//

#include "GeneratorRandom.h"

unique_ptr<vector<pair<double,double>>> GeneratorRandom::GenerateWorld(int size) {

  unique_ptr<vector<pair<double,double>>> world (new vector<pair<double,double>>());
  for (int i = 0; i < size; i ++) {
    world->push_back(make_pair<double, double>(1,1));
  }
  return move(world);
}