#include <memory>

using std::make_shared;

#include "euclidean_world_generator.h"

namespace TSP {

shared_ptr<World> EuclideanWorldGenerator::GenerateWorld(int n) {
  shared_ptr<Nodes2> nodes = GenerateNodes(n);
  n = nodes->size(); // because file generator actually ignores the "n" parameter

  shared_ptr<SquareMatrix<double>> world = make_shared<SquareMatrix<double>>(n);

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      (*world)[i][j] = (*world)[j][i] = (*nodes)[i].dist_to((*nodes)[j]);
    }
  }

  return make_shared<World>(World{n, WorldType::EUCLIDEAN2D, world, nodes});
}

} // namespace TSP
