#pragma once

#include "improvement_algorithm.h"

namespace TSP {

class Kopt2ImprovementAlgorithm : public ImprovementAlgorithm {
 public:
  void Reset() override;
  bool Iterate(int granularity) override;
  int GetMaxGranularity() override;
};

} // namespace TSP
