#pragma once

#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;

#include "point2.h"
#include "world.h"
//#include "world_generator.h"

namespace TSP {
//class EuclideanWorldGenerator : public WorldGenerator {
class EuclideanWorldGenerator {
 public:
  virtual ~EuclideanWorldGenerator() = 0;
  virtual shared_ptr<Nodes2> GenerateNodes(int n) = 0;

//  shared_ptr<World> GenerateWorld(int n) override;
  virtual shared_ptr<World> GenerateWorld(int n) = 0;
};
}
