//
// Created by Bojan Roško on 9/2/17.
//

#include "TSPState.h"

#include <exception>
#include <cmath>


using namespace std;

TSPState::TSPState(TSPWorldGenerator* generator, StateOptions &options):
    generator(generator), size(options.size){

}

TSPState::~TSPState() {

}

void TSPState::GenerateNewWorld() {
  nodes = generator->GenerateWorld(size);
}

double EuclidianDistance(pair<double, double> x, pair<double, double> y) {
  return sqrt( pow(y.first - x.first, 2) + pow(y.second - x.second, 2));
}

double TSPState::GetCost(int i, int j) {
  if (i < 0 || i >= nodes->size() || j < 0 || j >= nodes->size()) {
    throw new range_error("Selected nodes out of range");
  }

  return EuclidianDistance(nodes->at(i), nodes->at(j));
}

vector<int> TSPState::GetPath() {
  return path;
}

void TSPState::SetPath(vector<int>& new_path) {
  path = new_path;
}

vector<pair<double,double>>* TSPState::GetNodes() {
  return nodes.get();
}

