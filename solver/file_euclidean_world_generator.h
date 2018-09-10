#pragma once

#include <string>
#include <memory>

using std::string;
using std::unique_ptr;

#include "tsplib_parser.h"
#include "euclidean_world_generator.h"

namespace TSP {

class FileEuclideanWorldGenerator : public EuclideanWorldGenerator {
 public:
  /// This parameter doesn't do anything
  vector<Point2> GenerateNodes(int n) override;

  void SetFile(string file_path);
 private:
  unique_ptr<TSPLIBParser> parser_;
};

} // namespace TSP;


