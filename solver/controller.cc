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
  constructive_algorithm_->Iterate(granularity);
  state_->current_path_ = constructive_algorithm_->GetFinalPath();
}

void Controller::SetImprovementAlgorithm(shared_ptr<ImprovementAlgorithm> algorithm) {
  improvement_algorithm_ = algorithm;
  improvement_algorithm_->SetState(state_);
  improvement_algorithm_->Reset();
}

void Controller::IterateImprovementAlgorithm(int granularity) {
  improvement_algorithm_->Iterate(granularity);
}

shared_ptr<State> Controller::GetCurrentState() {
  return state_;
}

} // namespace TSP
