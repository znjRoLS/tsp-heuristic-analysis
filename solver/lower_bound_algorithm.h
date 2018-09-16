#pragma once

#include "algorithm.h"

namespace TSP {

class LowerBoundAlgorithm : public Algorithm {
 public:
    void SetWorld(shared_ptr<World> world);
  double GetFinalValue();
 protected:
  double value_;
    shared_ptr<const World> world_;
};

} // namespace TSP
