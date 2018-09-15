#pragma once

#include "improvement_algorithm.h"

namespace TSP {

class LinKernighanImprovementAlgorithm : public ImprovementAlgorithm {
 public:
  void Reset() override;
  bool Iterate(int granularity) override;
  int GetMaxGranularity() override;
};

} // namespace TSP
