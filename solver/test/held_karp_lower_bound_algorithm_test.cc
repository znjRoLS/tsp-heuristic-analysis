#include "gtest/gtest.h"
#include <memory>

#include "../held_karp_lower_bound_algorithm.h"

using std::make_shared;
using std::make_unique;
using std::unique_ptr;

using namespace TSP;

TEST(HeldKarpLowerBoundAlgorithmTest, SimpleTest) {

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



  unique_ptr<LowerBoundAlgorithm> algo = make_unique<HeldKarpLowerBoundAlgorithm>(0);
  algo->SetWorld(world);
  algo->Reset();

  ASSERT_TRUE(algo->Iterate(2));
  double prev = -1;
  while (algo->Iterate(2)) {
    double curr = algo->GetFinalValue();
    ASSERT_GE(curr, prev);
    prev = curr;
  }

  ASSERT_GE(4.0, prev);



  algo = make_unique<HeldKarpLowerBoundAlgorithm>(1);
  algo->SetWorld(world);
  algo->Reset();

  ASSERT_FALSE(algo->Iterate(2));
  prev = -1;
  ASSERT_GE(4.0, prev);



  algo = make_unique<HeldKarpLowerBoundAlgorithm>(2);
  algo->SetWorld(world);
  algo->Reset();

  ASSERT_FALSE(algo->Iterate(2));
  prev = -1;
  ASSERT_GE(4.0, prev);



  algo = make_unique<HeldKarpLowerBoundAlgorithm>(3);
  algo->SetWorld(world);
  algo->Reset();

  ASSERT_TRUE(algo->Iterate(2));
  prev = -1;
  while (algo->Iterate(2)) {
    double curr = algo->GetFinalValue();
    ASSERT_GE(curr, prev);
    prev = curr;
  }

  prev = -1;
  ASSERT_GE(4.0, prev);
}