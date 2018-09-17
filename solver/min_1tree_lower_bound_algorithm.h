#pragma once

#include "lower_bound_algorithm.h"
#include <unordered_set>
#include "square_matrix.h"
#include "pair_hash.h"

using std::unordered_set;
using std::pair;

namespace TSP {

class Min1treeLowerBoundAlgorithm : public LowerBoundAlgorithm {
 public:
  void Reset() override;
  bool Iterate(int granularity) override;
  int GetMaxGranularity() override;
 private:

  bool CheckFoundOptimalPath(unordered_set<pair<int,int>> edges);

  int current_node_;
};

} // namespace TSP
