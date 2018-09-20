#include "random_euclidean_world_generator.h"

#include <memory>
#include "random.h"

using std::shared_ptr;
using std::make_shared;

namespace TSP {

shared_ptr<Nodes2> RandomEuclideanWorldGenerator::GenerateNodes(int n) {
  shared_ptr<Nodes2> nodes = make_shared<Nodes2>((unsigned) n);

  for (int i = 0; i < n; i++) {
    (*nodes)[i] = {Random::GetDouble(), Random::GetDouble()};
  }

  return nodes;
}

shared_ptr<World> RandomEuclideanWorldGenerator::GenerateWorld(int n) {
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
