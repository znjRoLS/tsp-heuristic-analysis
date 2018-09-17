#include "gtest/gtest.h"
#include <memory>

#include "../min_1tree_lower_bound_algorithm.h"

using std::make_shared;
using std::make_unique;
using std::unique_ptr;

using namespace TSP;

TEST(Min1treeLowerBoundAlgorithmTest, SimpleTest) {

  shared_ptr<World> world = make_shared<TSP::World>(
      World{
          3,
          WorldType::EUCLIDEAN2D,
          make_shared<SquareMatrix<double>>(vector<vector<double>>{
              {0, 1, 2},
              {1, 0, 1.5},
              {2, 1.5, 0},
          }),
      }
  );

  unique_ptr<LowerBoundAlgorithm> algo = make_unique<Min1treeLowerBoundAlgorithm>();
  algo->SetWorld(world);
  algo->Reset();
  ASSERT_FALSE(algo->Iterate(0));
}