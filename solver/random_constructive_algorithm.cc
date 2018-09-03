#include "random.h"

#include "random_constructive_algorithm.h"

namespace TSP {

RandomConstructiveAlgorithm::RandomConstructiveAlgorithm(shared_ptr<World> world) :
    ConstructiveAlgorithm(world) {}

int RandomConstructiveAlgorithm::GetMaxGranularity() {
  return 2;
}

void RandomConstructiveAlgorithm::Reset() {
  int n = world_->size;

  unvisited_.clear();
  for (int i = 0; i < n; i++) {
    unvisited_.insert(i);
  }
  current_path_.clear();

  random_path_.resize(n + 1);
  for (int i = 0; i < n; i++) random_path_[i] = i;
  random_path_[n] = 0;
  Random::Randomize(&random_path_);
}

bool RandomConstructiveAlgorithm::Iterate(int granularity) {
  if (granularity == 1) {
    if (current_path_.size() == random_path_.size()) {
      return false;
    } else {
      current_path_.push_back(random_path_[current_path_.size()]);
      return true;
    }
  }
  if (granularity == 0) {
    while (Iterate(1)) {};
    return false;
  }
  return false;
}

} // namespace TSP
