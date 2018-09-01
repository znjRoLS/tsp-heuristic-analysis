#include "gtest/gtest.h"

#include "../state.h"

using namespace TSP;

TEST(MyTestTest, CurrentCost) {
    State state;
    ASSERT_EQ(0.0, state.CurrentCost());
}

