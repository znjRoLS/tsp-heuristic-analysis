#pragma once

#include "algorithm.h"

namespace TSP {

class LowerBoundAlgorithm : public Algorithm {
 public:
  double GetFinalValue();
 protected:
  double value_;
};

} // namespace TSP
