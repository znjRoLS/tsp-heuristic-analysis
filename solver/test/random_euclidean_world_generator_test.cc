#include "gtest/gtest.h"

#include "../random_euclidean_world_generator.h"

using namespace TSP;

TEST(RandomEuclideanWorldGeneratorTest, GeneratesRandom) {
  std::unique_ptr<RandomEuclideanWorldGenerator> generator = std::make_unique<RandomEuclideanWorldGenerator>();

  shared_ptr<Nodes2> nodes = generator->GenerateNodes(5);

  ASSERT_EQ(5, nodes->size());
  ASSERT_NE((*nodes)[0].x_, (*nodes)[0].y_);
  ASSERT_NE((*nodes)[0].x_, (*nodes)[1].x_);
}
