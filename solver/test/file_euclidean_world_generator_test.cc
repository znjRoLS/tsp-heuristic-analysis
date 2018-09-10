#include "gtest/gtest.h"
#include <memory>

#include "../file_euclidean_world_generator.h"

using std::make_unique;
using std::unique_ptr;

using namespace TSP;

TEST(FileEuclideanWorldGeneratorTest, SimpleTest) {
  unique_ptr<FileEuclideanWorldGenerator> generator = make_unique<FileEuclideanWorldGenerator>();

  generator->SetFile(TEST_DATA_LOCATION "VLSI/bcl380.tsp");

  vector<Point2> nodes = generator->GenerateNodes(0);

  ASSERT_EQ(nodes.size(), 380);
  Point2 first{0, 108};
  ASSERT_EQ(first, nodes[0]);

}
