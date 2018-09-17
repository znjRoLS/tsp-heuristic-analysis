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
  pair<int,int> GetNearestNodes(const shared_ptr<SquareMatrix<double>> distances, const int node) const;
  unordered_set<pair<int, int>> MST(const shared_ptr<SquareMatrix<double>> distances, const int node_to_skip) const;

  int current_node_;
};

} // namespace TSP