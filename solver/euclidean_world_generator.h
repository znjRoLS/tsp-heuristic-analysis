#pragma once

#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;

#include "point2.h"
#include "world.h"
#include "world_generator.h"

namespace TSP {
class EuclideanWorldGenerator : public WorldGenerator {
 public:
  virtual vector<Point2> GenerateNodes(int n) = 0;

  shared_ptr<World> GenerateWorld(int n) override;
};
}
