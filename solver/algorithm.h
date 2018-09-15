#pragma once

#include "world.h"
#include "util.h"

using std::pair;
using std::vector;

namespace TSP {

class Algorithm {
 public:
  virtual void Reset() = 0;
  virtual bool Iterate(int granularity) = 0;
  virtual int GetMaxGranularity() = 0;

  vector<VisualEdge> GetVisualization();

 protected:
  vector<VisualEdge> visualization_;

};

} // namespace TSP