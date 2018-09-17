#include "gtest/gtest.h"
#include "../alfa_measure.h"
#include "../world.h"

using std::make_shared;
using std::unique_ptr;
using std::make_unique;

using namespace TSP;

TEST(AlfaMeasureTest, SimpleTest) {
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

  auto alfa = AlfaMeasure(world->distances_, 0);

  vector<vector<double>> expected = {
      {0, 0.5, 0, 0},
      {0.5, 0, 0, 0},
      {0, 0, 0, 0.5},
      {0, 0, 0.5, 0},
  };

  ASSERT_EQ(alfa->GetData(), expected);
}
