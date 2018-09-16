#include "gtest/gtest.h"
#include <memory>

#include "../state.h"

using namespace TSP;
using std::make_shared;

TEST(StateTest, CurrentCost) {
  State state(
      make_shared<TSP::World>(
          World{
              3,
              WorldType::EUCLIDEAN2D,
              make_shared<SquareMatrix<double>>(vector<vector<double>>{
                  {0, 1, 2},
                  {1, 0, 1.5},
                  {2, 1.5, 0},
              }),
          }
      ),
      vector<int>{0, 1, 2, 0}
  );

  ASSERT_EQ(4.5, state.CurrentPathCost());
}
