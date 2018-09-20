#pragma once

#include <memory>

using std::shared_ptr;

#include "algorithm.h"
#include "state.h"

namespace TSP {

class ImprovementAlgorithm : public Algorithm {
 public:
  virtual ~ImprovementAlgorithm() = 0;
  void SetState(shared_ptr<State> state);

  double GetCurrentPathCost();

 protected:
  shared_ptr<State> state_;
};

} // namespace TSP
