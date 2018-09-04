#include <memory>

using std::make_shared;

#include "controller.h"

namespace TSP {

void Controller::SetWorldGenerator(shared_ptr<WorldGenerator> world_generator) {
  world_generator_ = world_generator;
}

void Controller::GenerateNewWorld(int size) {
  world_ = world_generator_->GenerateWorld(size);
  state_ = make_shared<State>(world_);
}

void Controller::SetConstructiveAlgorithm(shared_ptr<ConstructiveAlgorithm> algorithm) {
  constructive_algorithm_ = algorithm;
  constructive_algorithm_->SetWorld(world_);
  constructive_algorithm_->Reset();
}

void Controller::IterateConstructiveAlgorithm(int granularity) {
  constructive_algorithm_->Iterate(0); // TODO fix this
  state_->current_path_ = constructive_algorithm_->GetFinalPath();
}

shared_ptr<State> Controller::GetCurrentState() {
  return state_;
}

} // namespace TSP
