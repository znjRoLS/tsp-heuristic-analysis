#include "gtest/gtest.h"
#include "../kopt2_search_improvement_algorithm.h"

using std::make_shared;
using std::unique_ptr;
using std::make_unique;

using namespace TSP;

TEST(Kopt2SearchImprovementAlgorithmTest, SimpleTest) {
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

  unique_ptr<ImprovementAlgorithm> algo = make_unique<Kopt2SearchImprovementAlgorithm>();
  algo->SetState(state);
  algo->Reset();

  ASSERT_TRUE(algo->Iterate(2));

  Path path = vector<int>{0, 2, 1, 3, 0};

  ASSERT_EQ(state->current_path_, path);

  ASSERT_FALSE(algo->Iterate(0));
}
