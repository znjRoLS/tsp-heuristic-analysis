#include "state.h"

namespace TSP {

State::State(shared_ptr<TSP::World> world) :
    world_(world) {
  SetDefaultPath();
}

State::State(shared_ptr<TSP::World> world, TSP::Path path) :
    world_(world),
    current_path_(path) {

}

void State::SetDefaultPath() {
  current_path_.clear();
  for (int i = 0; i < world_->size; i++) {
    current_path_.push_back(i);
  }
  current_path_.push_back(0);
}

double State::CurrentPathCost() {
  return PathCost(current_path_, world_->distances_);
}

void State::UpdateOptimalPath(State state) {
  TSP_ASSERT_EQ(world_, state.world_);

  if (state.CurrentPathCost() < CurrentPathCost()) {
    current_path_ = state.current_path_;
  }
}

double State::PathCost(const Path& path, const shared_ptr<SquareMatrix<double>>& distances) {
  if (static_cast<int>(path.size()-1) != distances->Size().first) return 0.0;

  double sum = 0;
  int curr_node = path[0];
  for (unsigned i = 1; i < path.size(); i++) {
    int next_node = path[i];
    sum += (*distances)[curr_node][next_node];
    curr_node = next_node;
  }
  sum += (*distances)[curr_node][path[0]];
  return sum;
}

} // namespace TSP