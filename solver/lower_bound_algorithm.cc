#include "lower_bound_algorithm.h"

namespace TSP {

LowerBoundAlgorithm::~LowerBoundAlgorithm() {}

void LowerBoundAlgorithm::SetWorld(shared_ptr<TSP::World> world) {
  world_ = world;
}

double LowerBoundAlgorithm::GetFinalValue() {
  return value_;
}

bool LowerBoundAlgorithm::FoundOptimalSolution() {
  return !optimal_path_.empty();
}
Path LowerBoundAlgorithm::GetOptimalPath() {
  return optimal_path_;
}

}