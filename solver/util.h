#pragma once

#include <vector>
#include <cassert>
#include "point2.h"

#define TSP_ASSERT(x) assert(x);
#define TSP_ASSERT_EQ(x, y) TSP_ASSERT(x == y)
#define TSP_ASSERT_CONTAINS(x, y) TSP_ASSERT(x.find(y) != x.end())
#define TSP_ILLEGAL TSP_ASSERT(false)

namespace TSP {

/// Path type representing a solution Path in TSP
typedef std::vector<int> Path;

typedef std::vector<Point2> Nodes2;

enum GlobalColor {
  color0,
  color1,
  black,
  white,
  darkGray,
  gray,
  lightGray,
  red,
  green,
  blue,
  cyan,
  magenta,
  yellow,
  darkRed,
  darkGreen,
  darkBlue,
  darkCyan,
  darkMagenta,
  darkYellow,
  transparent
};

struct VisualEdge {
  int n1;
  int n2;
  GlobalColor color;
  double strength;
};

} // namespace TSP
