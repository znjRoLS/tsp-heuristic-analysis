#pragma once

#include <vector>
#include <cassert>
#include "point2.h"

#define TSP_ASSERT(x) assert(x);
#define TSP_ASSERT_EQ(x, y) TSP_ASSERT(x == y)

namespace TSP {

/// Path type representing a solution Path in TSP
typedef std::vector<int> Path;

typedef std::vector<Point2> Nodes2;

} // namespace TSP
