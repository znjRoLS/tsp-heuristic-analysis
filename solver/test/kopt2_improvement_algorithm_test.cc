#include "gtest/gtest.h"
#include "../kopt2_improvement_algorithm.h"

using std::make_shared;
using std::unique_ptr;
using std::make_unique;

using namespace TSP;

TEST(Kopt2ImprovementAlgorithmTest, ImprovementAlgorithmWorks) {
  shared_ptr<State> state = make_shared<State>(
      make_shared<TSP::World>(
          World{
              4,
              WorldType::EUCLIDEAN2D,
              make_shared<Matrix<double>>(vector<vector<double>>{
                  // square
                  {0, 1.5, 1, 1},
                  {1.5, 0, 1, 1},
                  {1, 1, 0, 1.5},
                  {1, 1, 1.5, 0},
              }),
          }
      ),
      vector<int>{0, 1, 2, 3, 0}
  );

  unique_ptr<ImprovementAlgorithm> algo = make_unique<Kopt2ImprovementAlgorithm>();
  algo->SetState(state);
  algo->Reset();
  ASSERT_TRUE(algo->Iterate(0));

  bool changed = false;

  for (int i = 0; i < 1000; i++) {

    algo->Iterate(0);

    if (state->current_path_ != vector<int>{0, 1, 2, 3, 0}) {
      changed = true;
      break;
    }

  }

  ASSERT_TRUE(changed);
}

TEST(Kopt2ImprovementAlgorithmTest, DoesntImproveOptimal) {
  shared_ptr<State> state = make_shared<State>(
      make_shared<TSP::World>(
          World{
              4,
              WorldType::EUCLIDEAN2D,
              make_shared<Matrix<double>>(vector<vector<double>>{
                  // square
                  {0, 1.5, 1, 1},
                  {1.5, 0, 1, 1},
                  {1, 1, 0, 1.5},
                  {1, 1, 1.5, 0},
              }),
          }
      ),
      vector<int>{0, 2, 1, 3, 0}
  );

  unique_ptr<ImprovementAlgorithm> algo = make_unique<Kopt2ImprovementAlgorithm>();
  algo->SetState(state);
  algo->Reset();
  ASSERT_TRUE(algo->Iterate(0));

  bool changed = false;

  for (int i = 0; i < 1000; i++) {

    algo->Iterate(0);

    if (state->current_path_ != vector<int>{0, 2, 1, 3, 0}) {
      changed = true;
      break;
    }

  }

  ASSERT_FALSE(changed);
}
