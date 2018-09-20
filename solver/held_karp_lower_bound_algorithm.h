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
  HeldKarpLowerBoundAlgorithm(int variant);
  void Reset() override;
  bool Iterate(int granularity) override;

  void IterateOptimized() override;

  int GetMaxGranularity() override;
 private:

  bool CheckFoundOptimalPath(unordered_set<pair<int, int>> edges);

  bool IteratePi_0(unordered_set<pair<int, int>> min_1tree, double W);
  bool IteratePi_2(unordered_set<pair<int, int>> min_1tree, double W);
  bool IteratePi_3(unordered_set<pair<int, int>> min_1tree, double W);

  // Variant 0:
  //   - Checking all min1trees
  //   - Using simple step size iteration:
  //     - The step size is constant for a fixed number of iterations, called a period.
  //     - When a period is finished, both the length of the period and the step size are halved.
  //     - The length of the first period is set to n/2, where n is the number of cities.
  //     - The initial step size, t0, is set to 1, but is doubled in the beginning of the
  //         first period until W does not increase, i.e., w(πk)≤w(πk-1). When this
  //         happens, the step size remains constant for the rest of the period.
  //     - The algorithm terminates when either the length of the period or vk becomes zero.
  //     - If the last iteration of a period leads to an increment of W, then the period
  //         is doubled.
  //
  // Variant 1, change to variant 0:
  //   - Using just one (0) node for min1tree
  //
  // Variant 2, in addition to variant 1:
  //   - The updating of π, i.e.,πk+1=πk+ tkvk, is replaced by πk+1=πk+ k(0.7vk+ 0.3vk-1), where v-1= v0
  //   - The special node for the 1-tree computations is not fixed. A minimum
  //       1-tree is determined by computing a minimum spanning tree and then
  //       adding an edge corresponding to the second nearest neighbor of one of
  //       the leaves of the tree. The leaf chosen is the one that has the longest
  //       second nearest neighbor distance.
  //
  //
  // Variant 3:
  //   - Checking all min1trees
  //   - Using gradient descent:
  //      - While there is improvement, increase step size
  //      - When there is no improvement, decrese step size
  //      - Use inertia
  //      - When there is no global improvement for 10 steps, terminate
  //
  int variant_;

  shared_ptr<SquareMatrix<double>> distances_;

  unordered_set<pair<int, int>> min_1tree_;

  struct step_data {
    vector<double> pi_;
    vector<int> v_;

    int current_period_;
    int current_iter_;
    double t_;

    int iter_no_increase_;
    double w_;
    bool initial_increase_;

    const double v_intertia_ = 0.3;
    const double largest_t_ratio = 100;
    double largest_t_;
  } step_data_;

  double curr_max_1tree_;

  int current_node_;
};

} // namespace TSP
