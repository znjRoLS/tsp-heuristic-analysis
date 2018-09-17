#pragma once

#include "world.h"
#include "util.h"
#include <unordered_map>

using std::pair;
using std::vector;
using std::unordered_map;
using std::string;

namespace TSP {

class Algorithm {
 public:
  virtual void Reset() = 0;
  virtual bool Iterate(int granularity) = 0;
  virtual int GetMaxGranularity() = 0;

  vector<VisualEdge> GetVisualization();
  unordered_map<string, string> GetVisualParams();

 protected:
  vector<VisualEdge> visualization_;
  unordered_map<string, string> visual_params_;

};

} // namespace TSP