#include "file_euclidean_world_generator.h"

#include <iostream>
#include <fstream>

using std::ifstream;
using std::make_unique;

namespace TSP {

vector<Point2> FileEuclideanWorldGenerator::GenerateNodes(int n) {
  vector<Point2> res;

  while (parser_->IterateNextPoint()) {
    res.push_back(parser_->GetNextPoint());
  }

  return res;
}

void FileEuclideanWorldGenerator::SetFile(string file_path) {
  parser_ = make_unique<TSPLIBParser>(file_path);
}

} // namespace TSP