#include "gtest/gtest.h"
#include "../random_constructive_algorithm.h"

using std::make_shared;
using std::unique_ptr;
using std::make_unique;

using namespace TSP;

TEST(RandomConstructiveAlgorithmTest, ConstructsRandomPath) {
  shared_ptr<World> world = make_shared<TSP::World>(
      World{
          3,
          WorldType::EUCLIDEAN,
          make_shared<Matrix<double>>(vector<vector<double>>{
              {0, 1, 2},
              {1, 0, 1.5},
              {2, 1.5, 0},
          }),
      }
  );

  unique_ptr<ConstructiveAlgorithm> algo = make_unique<RandomConstructiveAlgorithm>(world);
  algo->Reset();
  ASSERT_FALSE(algo->Iterate(0));

  ASSERT_EQ(algo->GetFinalPath().size(), 4);

  algo->Reset();
  ASSERT_TRUE(algo->Iterate(1));
  ASSERT_TRUE(algo->Iterate(1));
  ASSERT_TRUE(algo->Iterate(1));
  ASSERT_FALSE(algo->Iterate(0));
}
