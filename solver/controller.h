#pragma once

#include <memory>

using std::shared_ptr;

#include "state.h"
#include "world_generator.h"
#include "constructive_algorithm.h"

namespace TSP {

class Controller {
 public:

  void SetWorldGenerator(shared_ptr<WorldGenerator> world_generator);
  void GenerateNewWorld(int size);

  void SetConstructiveAlgorithm(shared_ptr<ConstructiveAlgorithm> algorithm);
  void IterateConstructiveAlgorithm(int granularity);

  shared_ptr<State> GetCurrentState();

 private:
  shared_ptr<WorldGenerator> world_generator_;

  shared_ptr<World> world_;
  shared_ptr<State> state_;

  shared_ptr<ConstructiveAlgorithm> constructive_algorithm_;
};

} // namespace TSP
