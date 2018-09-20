#pragma once

#include "algorithm.h"

namespace TSP {

class LowerBoundAlgorithm : public Algorithm {
 public:
  virtual ~LowerBoundAlgorithm() = 0;
  void SetWorld(shared_ptr<World> world);
  double GetFinalValue();
  bool FoundOptimalSolution();
  Path GetOptimalPath();
  virtual void IterateOptimized() = 0;

 protected:
  double value_;
  shared_ptr<const World> world_;
  Path optimal_path_;
};

} // namespace TSP
