#include "file_euclidean_world_generator.h"

#include <iostream>
#include <fstream>

using std::ifstream;
using std::make_unique;
using std::make_shared;

namespace TSP {

shared_ptr<Nodes2> FileEuclideanWorldGenerator::GenerateNodes(int n) {
  shared_ptr<Nodes2> res = make_shared<Nodes2>();

  while (parser_->IterateNextPoint()) {
    res->push_back(parser_->GetNextPoint());
  }

  return res;
}

void FileEuclideanWorldGenerator::SetFile(string file_path) {
  parser_ = make_unique<TSPLIBParser>(file_path);
}


shared_ptr<World> FileEuclideanWorldGenerator::GenerateWorld(int n) {
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