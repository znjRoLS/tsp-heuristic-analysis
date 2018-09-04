#include "constructive_algorithm.h"

namespace TSP {

void ConstructiveAlgorithm::SetWorld(shared_ptr<TSP::World> world) {
  world_ = world;
}

Path ConstructiveAlgorithm::GetFinalPath() {
  return current_path_;
}

} // namespace TSP