//
// Created by Bojan Roško on 9/2/17.
//

#include "Util.h"

#include <exception>
#include <cmath>
#include <cassert>
#include <random>
#include <ctime>

#define EPS 1e-7

double GetCost(const World& world, unsigned i, unsigned j) {
  if (i < 0 || i >= world->size() || j < 0 || j >= world->size()) {
    throw new range_error("Selected nodes out of range");
  }

  return EuclidianDistance(world->at(i), world->at(j));
}

double GetCost(const World& world, const Path& path) {
  double cost = GetCost(world, path->at(0), path->at(path->size()-1));
  for (unsigned i = 1; i < path->size(); i ++) {
    cost += GetCost(world, path->at(i-1), path->at(i));
  }
  return cost;
}

void SetMin(const World& world, Path& path1, Path& path2) {
  if (Less(world, path2, path1)) {
    for (unsigned i = 0; i < path1->size(); i++) {
      path1->at(i) = path2->at(i);
    }
  }
}

bool Less(const World& world, Path& path1, Path& path2) {
  double cost1 = GetCost(world, path1);
  double cost2 = GetCost(world, path2);
  return Less(cost1, cost2);
}

double EuclidianDistance(Point2 x, Point2 y) {
  return sqrt( pow(y.first - x.first, 2) + pow(y.second - x.second, 2));
}

ostream& operator<<(ostream& out, const Point2& point) {
  out << "{" << point.first << ", " << point.second << "}";
  return out;
}

double Random(){
  static bool initialized = false;

  if (!initialized) {
    initialized = true;
    srand(time(0));
  }

  return ((double) rand() / (RAND_MAX));
}

bool Equal(double x, double y) {
  return fabs(x-y) < EPS;
}

bool Less(double x, double y) {
  return !Equal(x,y) && x < y;
}

bool Greater(double x, double y) {
  return !Equal(x,y) && x > y;
}

bool LessOrEqual(double x, double y) {
  return !Greater(x,y);
}

bool GreaterOrEqual(double x, double y) {
  return !Less(x,y);
}

double WeightedRandom(const vector<double> &weights, const vector<double> &values) {
  assert(weights.size() == values.size());

  double sum = accumulate(weights.begin(), weights.end(), 0);

  default_random_engine random_engine;
  uniform_real_distribution<double> distribution(0.0, sum);

  double random_value = distribution(random_engine);

  unsigned weight_ind = -1;
  while(random_value > 0) {
    if (weight_ind == weights.size() - 1){
      return values[weight_ind];
    }
    random_value -= weights[++weight_ind];
  }

  return values[weight_ind];

}

int WeightedRandom(const vector<double> &weights, const vector<int> &values) {
  assert(weights.size() == values.size());

  double sum = accumulate(weights.begin(), weights.end(), 0);

  default_random_engine random_engine;
  uniform_real_distribution<double> distribution(0.0, sum);

  double random_value = distribution(random_engine);

    unsigned weight_ind = -1;
  while(random_value > 0) {
    if (weight_ind == weights.size() - 1){
      return values[weight_ind];
    }
    random_value -= weights[++weight_ind];
  }

  return values[weight_ind];

}