#pragma once

#include <memory>

using std::shared_ptr;

#include "algorithm.h"
#include "state.h"

namespace TSP {

class ImprovementAlgorithm : public Algorithm {
 public:
  void SetState(shared_ptr<State> state);

 protected:
  shared_ptr<State> state_;
};

} // namespace TSP
