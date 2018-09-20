#pragma once

#include "improvement_algorithm.h"

namespace TSP {

class Kopt3SearchImprovementAlgorithm : public ImprovementAlgorithm {
 public:
  void Reset() override;
  bool Iterate(int granularity) override;
  int GetMaxGranularity() override;
 private:
  double GetCost(int x1, int x2, int y1, int y2, int z1, int z2);

  int current_search_first_edge_ = 0;
  int current_search_second_edge_ = 2;
  int current_search_third_edge_ = 4;
  bool reset_ = true;
};

} // namespace TSP
