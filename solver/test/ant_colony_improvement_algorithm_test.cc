#include "gtest/gtest.h"
#include "../ant_colony_improvement_algorithm.h"

using std::make_shared;
using std::unique_ptr;
using std::make_unique;

using namespace TSP;

TEST(AntColonyImprovementAlgorithm, SimpleTest) {

  shared_ptr<State> state = make_shared<State>(
      make_shared<TSP::World>(
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
      ),
      vector<int>{0, 1, 2, 3, 0}
  );

  unique_ptr<ImprovementAlgorithm> algo = make_unique<AntColonyImprovementAlgorithm>(0, 10, 1, 3, 0.5, 10);
  algo->SetState(state);
  algo->Reset();

  ASSERT_TRUE(algo->Iterate(0));

}