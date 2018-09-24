#pragma once

#include "constructive_algorithm.h"
#include <deque>

using std::deque;

namespace TSP {

class NearestNeighbourDoubleEndedConstructiveAlgorithm : public ConstructiveAlgorithm {
 public:
  void Reset() override;
  bool Iterate(int granularity) override;
  int GetMaxGranularity() override;
 private:

  unordered_set<int> unvisited_;

  unordered_set<int>::iterator current_processing_;
  int current_closest_;
  int current_last_head_;
  int current_last_tail_;
  double current_closest_dist_;
  bool current_closest_head_;
  bool current_processing_head_;

  deque<int> path_;

};

} // namespace TSP
