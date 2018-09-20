#include "improvement_algorithm.h"

namespace TSP {

ImprovementAlgorithm::~ImprovementAlgorithm() {}

void ImprovementAlgorithm::SetState(shared_ptr<State> state) {
  state_ = state;
  SetMeasureForOptimizing(state->world_->distances_);
}

double ImprovementAlgorithm::GetCurrentPathCost() {
  return state_->CurrentPathCost();
}

} // namespace TSP