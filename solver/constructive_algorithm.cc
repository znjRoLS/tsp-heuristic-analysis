#include "constructive_algorithm.h"

#include "state.h"

namespace TSP {

void ConstructiveAlgorithm::SetWorld(shared_ptr<TSP::World> world) {
  world_ = world;
}

Path ConstructiveAlgorithm::GetFinalPath() {
  return current_path_;
}

double ConstructiveAlgorithm::GetFinalPathCost() {
  if (static_cast<int>(current_path_.size()) != world_->size + 1) return 0.0;
  return State::PathCost(current_path_, world_->distances_);
}

} // namespace TSP