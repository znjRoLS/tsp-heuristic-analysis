#include "gtest/gtest.h"
#include <memory>

#include "../euclidean_world_generator.h"
#include "../random_euclidean_world_generator.h"

using namespace TSP;

TEST(EuclideanWorldGeneratorTest, ConstructsDistancesFromNodes) {
  std::unique_ptr<EuclideanWorldGenerator> generator = std::make_unique<RandomEuclideanWorldGenerator>();

  shared_ptr<World> world = generator->GenerateWorld(5);

  tuple<int, int> size_tuple = {5, 5};

  ASSERT_EQ(size_tuple, world->distances_->size());
  ASSERT_GE((*world->distances_)[0][1] + (*world->distances_)[1][2], (*world->distances_)[0][2]);
  ASSERT_EQ((*world->distances_)[0][0], 0.0);
}
