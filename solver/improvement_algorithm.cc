#include "improvement_algorithm.h"

namespace TSP {

void ImprovementAlgorithm::SetState(shared_ptr<State> state) {
  state_ = state;
}

double ImprovementAlgorithm::GetCurrentPathCost() {
  return state_->CurrentPathCost();
}

} // namespace TSP