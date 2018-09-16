#include "lower_bound_algorithm.h"

namespace TSP {

void LowerBoundAlgorithm::SetWorld(shared_ptr<TSP::World> world) {
  world_ = world;
}

double LowerBoundAlgorithm::GetFinalValue() {
  return value_;
}

}