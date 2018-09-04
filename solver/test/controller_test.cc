#include "gtest/gtest.h"
#include "../controller.h"
#include "../random_euclidean_world_generator.h"
#include "../random_constructive_algorithm.h"

using std::make_shared;
using std::unique_ptr;
using std::make_unique;

using namespace TSP;

TEST(SolverTest, ConstructsTest) {

  Controller controller;

  controller.SetWorldGenerator(make_shared<RandomEuclideanWorldGenerator>());
  controller.GenerateNewWorld(5);
  controller.SetConstructiveAlgorithm(make_shared<RandomConstructiveAlgorithm>());
  controller.IterateConstructiveAlgorithm(0);

  ASSERT_EQ(controller.GetCurrentState()->current_path_.size(), 6);
}
