//
// Created by rols on 9/3/2018.
//
#include "gtest/gtest.h"
#include <memory>

#include "../random_euclidean_world_generator.h"

using namespace TSP;

TEST(RandomEuclideanWorldGeneratorTest, GeneratesRandom) {
    std::unique_ptr<RandomEuclideanWorldGenerator> generator = std::make_unique<RandomEuclideanWorldGenerator>();

    vector<Point2> nodes = generator->GenerateNodes(5);

    ASSERT_EQ(5, nodes.size());
    ASSERT_NE(nodes[0].x_, nodes[0].y_);
    ASSERT_NE(nodes[0].x_, nodes[1].x_);
}