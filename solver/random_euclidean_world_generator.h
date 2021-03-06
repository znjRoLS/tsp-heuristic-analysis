#pragma once

#include "euclidean_world_generator.h"

namespace TSP {
class RandomEuclideanWorldGenerator : public EuclideanWorldGenerator {
 public:
  shared_ptr<Nodes2> GenerateNodes(int n) override;
  shared_ptr<World> GenerateWorld(int n) override;
};
} // namespace TSP
