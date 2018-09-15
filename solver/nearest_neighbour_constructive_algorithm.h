#pragma once

#include "constructive_algorithm.h"
#include <unordered_set>

using std::unordered_set;

namespace TSP {

class NearestNeighbourConstructiveAlgorithm : public ConstructiveAlgorithm {
 public:
  void Reset() override;
  bool Iterate(int granularity) override;
  int GetMaxGranularity() override;
 private:

  unordered_set<int> unvisited_;

  unordered_set<int>::iterator current_processing_;
  int current_closest_;
  int current_last_;
  double current_closest_dist_;


};

} // namespace TSP

