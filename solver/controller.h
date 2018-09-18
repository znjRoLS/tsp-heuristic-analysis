#pragma once

#include <memory>

using std::shared_ptr;

#include "state.h"
#include "euclidean_world_generator.h"
#include "constructive_algorithm.h"
#include "improvement_algorithm.h"

namespace TSP {

class Controller {
 public:

  void SetWorldGenerator(shared_ptr<EuclideanWorldGenerator> world_generator);
  void GenerateNewWorld(int size);

  void SetConstructiveAlgorithm(shared_ptr<ConstructiveAlgorithm> algorithm);
  void IterateConstructiveAlgorithm(int granularity);
  void IterateOptimizedConstructiveAlgorithm();

  void SetImprovementAlgorithm(shared_ptr<ImprovementAlgorithm> algorithm);
  void IterateImprovementAlgorithm(int granularity);
  void IterateOptimizedImprovementAlgorithm();

  shared_ptr<State> GetCurrentState();

 private:
  shared_ptr<EuclideanWorldGenerator> world_generator_;

  shared_ptr<World> world_;
  shared_ptr<State> state_;

  shared_ptr<ConstructiveAlgorithm> constructive_algorithm_;
  shared_ptr<ImprovementAlgorithm> improvement_algorithm_;
};

} // namespace TSP
