#pragma once

#include "world.h"

using std::pair;
using std::vector;

namespace TSP {

class Algorithm {
 public:
  virtual void Reset() = 0;
  virtual bool Iterate(int granularity) = 0;
  virtual int GetMaxGranularity() = 0;

  vector<pair<pair<int,int>, double>> GetVisualization();

 protected:
  vector<pair<pair<int,int>, double>> visualization_;

};

} // namespace TSP