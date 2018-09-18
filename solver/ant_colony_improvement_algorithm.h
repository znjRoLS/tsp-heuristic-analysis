#pragma once

#include "improvement_algorithm.h"

namespace TSP {

class AntColonyImprovementAlgorithm : public ImprovementAlgorithm {
 public:
  AntColonyImprovementAlgorithm(int variant, int num_ants, double alfa, double beta, double ro, double q, double phi);
  void Reset() override;
  bool Iterate(int granularity) override;
  int GetMaxGranularity() override;
 private:

  struct Ant {
    unordered_set<int> unvisited_;
    Path current_path_;
  };

  int AntChosePath(const Ant &ant,
                   const shared_ptr<SquareMatrix<double>> &pheromones,
                   const shared_ptr<SquareMatrix<double>> &distances);
  void UpdatePheromones();

  shared_ptr<SquareMatrix<double>> pheromones_;
  vector<Ant> ants_;

  int current_ant_;

  int current_cost_ant_;
  int current_best_ant_;
  double current_best_ant_cost_;

  const int variant_;
  const int num_ants_;
  const double alfa_;
  const double beta_;
  const double ro_;
  const double q_;
  const double phi_;
};

} // namespace TSP

