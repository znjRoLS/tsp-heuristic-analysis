//
// Created by Bojan Roško on 9/2/17.
//

#include "Util.h"

#include <exception>
#include <cmath>

double GetCost(const World& world, int i, int j) {
  if (i < 0 || i >= world->size() || j < 0 || j >= world->size()) {
    throw new range_error("Selected nodes out of range");
  }

  return EuclidianDistance(world->at(i), world->at(j));
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