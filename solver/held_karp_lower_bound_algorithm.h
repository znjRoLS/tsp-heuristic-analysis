#pragma once

#include "lower_bound_algorithm.h"
#include <unordered_set>
#include "square_matrix.h"
#include "pair_hash.h"

using std::unordered_set;
using std::pair;

namespace TSP {

class HeldKarpLowerBoundAlgorithm : public LowerBoundAlgorithm {
public:
    void Reset() override;
    bool Iterate(int granularity) override;
    int GetMaxGranularity() override;
 private:
  bool IteratePi(unordered_set<pair<int,int>> min_1tree);
  unordered_set<pair<int, int>> Min1Tree(const shared_ptr<SquareMatrix<double>> distances, const int special_node) const;

  shared_ptr<SquareMatrix<double>> distances_;
  vector<double> pi_;
  unordered_set<pair<int, int>> min_1tree_;

  int current_node_;
};

} // namespace TSP
