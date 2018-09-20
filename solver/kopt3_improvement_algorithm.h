#pragma once

#include "improvement_algorithm.h"

namespace TSP {

class Kopt3ImprovementAlgorithm : public ImprovementAlgorithm {
 public:
  void Reset() override;
  bool Iterate(int granularity) override;
  int GetMaxGranularity() override;
 private:
  double GetCost(int x1, int x2, int y1, int y2, int z1, int z2);
};

} // namespace TSP
