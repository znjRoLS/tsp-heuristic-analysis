#include "kopt2_improvement_algorithm.h"

#include <algorithm>

using std::reverse;

#include "random.h"
#include "double_compare.h"

namespace TSP {

void Kopt2ImprovementAlgorithm::Reset() {

}

bool Kopt2ImprovementAlgorithm::Iterate(int granularity) {

  int n = state_->current_path_.size() - 1;

  TSP_ASSERT(n >= 4);

  if (granularity == 0) {

    visualization_.clear();

    int a = Random::GetInt(n - 1);
    int b = a + 1;

    // This way we don't chose nodes from the first edge.
    // Chose n-3 starting nodes, from the second node of the first edge.
    int c = Random::GetInt(n - 3 - 1);
    c += 1 + b;
    c %= n;
    int d = c + 1;

    int node_a = state_->current_path_[a];
    int node_b = state_->current_path_[b];
    int node_c = state_->current_path_[c];
    int node_d = state_->current_path_[d];


    // a - b is the first edge and c - d is the second one, so the path goes as following:
    //   0 ... x - a - b - x ... x - c - d - x ... 0
    // We should try to invert the b - c section

    double first_edge = (*state_->world_->distances_)[node_a][node_b];
    double second_edge = (*state_->world_->distances_)[node_c][node_d];
    double new_first_edge = (*state_->world_->distances_)[node_a][node_c];
    double new_second_edge = (*state_->world_->distances_)[node_b][node_d];

    if (DOUBLE_LESS(new_first_edge + new_second_edge, first_edge + second_edge)) {
      if (a < c) {
        reverse(state_->current_path_.begin() + b, state_->current_path_.begin() + d);
      } else {
        reverse(state_->current_path_.begin() + d, state_->current_path_.begin() + b);
      }

      visualization_.push_back( {node_a, node_b, GlobalColor::red, 0.5});
      visualization_.push_back( {node_c, node_d, GlobalColor::red, 0.5});
      visualization_.push_back( {node_a, node_c, GlobalColor::green, 1.0});
      visualization_.push_back({node_b, node_d, GlobalColor::green, 1.0});
    } else {

      visualization_.push_back( {node_a, node_b, GlobalColor::green, 1.0});
      visualization_.push_back( {node_c, node_d, GlobalColor::green, 1.0});
      visualization_.push_back( {node_a, node_c, GlobalColor::lightGray, 0.5});
      visualization_.push_back({node_b, node_d, GlobalColor::lightGray, 0.5});
    }
  }

  return true;
}

int Kopt2ImprovementAlgorithm::GetMaxGranularity() {
  return 0;
}

} // namespace TSP