#include "random.h"

#include "random_euclidean_world_generator.h"

namespace TSP {

vector<Point2> RandomEuclideanWorldGenerator::GenerateNodes(int n) {
  vector<Point2> nodes((unsigned) n);

  for (int i = 0; i < n; i++) {
    nodes[i] = {Random::GetDouble(), Random::GetDouble()};
  }

  return nodes;
}

} // namespace TSP
