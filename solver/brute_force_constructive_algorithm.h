#pragma once

#include "constructive_algorithm.h"

namespace TSP {

class BruteForceConstructiveAlgorithm : public ConstructiveAlgorithm {
 public:
  void Reset() override;
  bool Iterate(int granularity) override;
  int GetMaxGranularity() override;
 private:
  void SetVisuals();

  Path current_brute_force_path_;
  double current_path_cost_;
};

} // namespace TSP
