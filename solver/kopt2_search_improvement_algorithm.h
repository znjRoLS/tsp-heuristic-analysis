#pragma once

#include "improvement_algorithm.h"

namespace TSP {

class Kopt2SearchImprovementAlgorithm : public ImprovementAlgorithm {
 public:
  void Reset() override;
  bool Iterate(int granularity) override;
  int GetMaxGranularity() override;
 private:
  int current_search_first_edge_ = 0;
  int current_search_second_edge_ = 2;
  bool reset_ = true;
};

} // namespace TSP
