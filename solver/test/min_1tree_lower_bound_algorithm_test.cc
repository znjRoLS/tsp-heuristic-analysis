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
          4,
          WorldType::EUCLIDEAN2D,
          make_shared<SquareMatrix<double>>(vector<vector<double>>{
              // square
              // 2 | 1
              // - - -
              // 0 | 3
              {0, 1.5, 1, 1},
              {1.5, 0, 1, 1},
              {1, 1, 0, 1.5},
              {1, 1, 1.5, 0},
          }),
      }
  );

  unique_ptr<LowerBoundAlgorithm> algo = make_unique<Min1treeLowerBoundAlgorithm>();
  algo->SetWorld(world);
  algo->Reset();
  
  ASSERT_TRUE(algo->Iterate(1));
  double prev = 0;
  while (algo->Iterate(1)) {
    double curr = algo->GetFinalValue();
    ASSERT_GE(curr, prev);
    prev = curr;
  }
  
  ASSERT_GE(4.0, prev);
}