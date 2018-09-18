#include "ant_colony_improvement_algorithm.h"

#include <memory>

using std::make_shared;

namespace TSP {

void AntColonyImprovementAlgorithm::Reset() {

  ants_.clear();

  pheromones_ = make_shared<SquareMatrix<double>> (world_->size);
}

bool AntColonyImprovementAlgorithm::Iterate(int granularity) {
  return false;
}

int AntColonyImprovementAlgorithm::GetMaxGranularity() {
  return 0;
}

};// namespace TSP
