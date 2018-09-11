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

} // namespace TSP