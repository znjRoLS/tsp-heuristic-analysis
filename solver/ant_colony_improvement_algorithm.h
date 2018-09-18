#pragma once

#include "improvement_algorithm.h"

namespace TSP {

class AntColonyImprovementAlgorithm : public ImprovementAlgorithm {
 public:
  void Reset() override;
  bool Iterate(int granularity) override;
  int GetMaxGranularity() override;
 private:

  struct Ant {
    unordered_set<int> unvisited_;
    Path current_path_;
  };

  shared_ptr<SquareMatrix<double>> pheromones_;
  vector<Ant> ants_;
};

} // namespace TSP

