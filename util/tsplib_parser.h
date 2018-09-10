#pragma once

#include <string>
#include <fstream>

using std::string;
using std::ifstream;
using std::pair;

#include "point2.h"

/// This class knows how to parse only the following type of tsplib format:
/// EDGE_WEIGHT_TYPE : EUC_2D
///    NODE_COORD_SECTION
class TSPLIBParser {
 public:
  TSPLIBParser(string file_path);
  ~TSPLIBParser();

  bool IterateNextPoint();
  Point2 GetNextPoint();
  string GetInfo();

 private:
  ifstream input_file_;

  bool info_processed_;
  Point2 point_;

  string info_;
};
