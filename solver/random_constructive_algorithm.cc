#include "random.h"

#include "random_constructive_algorithm.h"

namespace TSP {

int RandomConstructiveAlgorithm::GetMaxGranularity() {
  return 1;
}

void RandomConstructiveAlgorithm::Reset() {
  int n = world_->size;

  unvisited_.clear();
  for (int i = 0; i < n; i++) {
    unvisited_.insert(i);
  }
  current_path_.clear();

  current_path_.push_back(0);

  visualization_.clear();

  random_path_.resize(n + 1);
  for (int i = 0; i < n; i++) random_path_[i] = i;
  random_path_[n] = 0;
  Random::Shuffle(random_path_.begin() + 1, random_path_.end() - 1);
}

bool RandomConstructiveAlgorithm::Iterate(int granularity) {
  if (granularity == 1) {

    if (!visualization_.empty()) {
      visualization_.rbegin()->color = GlobalColor::lightGray;
    }

    current_path_.push_back(random_path_[current_path_.size()]);

    visualization_.push_back({current_path_[current_path_.size() - 2], current_path_[current_path_.size() - 1],
                              GlobalColor::green, 0.5});

    return (current_path_.size() != random_path_.size());

  }
  if (granularity == 0) {
    while (Iterate(1)) {};
    return false;
  }
  return false;
}

} // namespace TSP
