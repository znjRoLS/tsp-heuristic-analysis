#pragma once

#include "world.h"

namespace TSP {

class Algorithm {
 public:
  virtual void Reset() = 0;
  virtual bool Iterate(int granularity) = 0;
  virtual int GetMaxGranularity() = 0;
};

} // namespace TSP