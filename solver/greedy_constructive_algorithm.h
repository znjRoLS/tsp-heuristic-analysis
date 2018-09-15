#pragma once

#include "constructive_algorithm.h"

#include <map>
#include <unordered_map>
#include <unordered_set>
#include "disjoint_set.h"
#include <memory>

using std::unique_ptr;
using std::multimap;
using std::unordered_map;
using std::unordered_set;

namespace TSP {

class GreedyConstructiveAlgorithm : public ConstructiveAlgorithm {
 public:
  void Reset() override;
  bool Iterate(int granularity) override;
  int GetMaxGranularity() override;
 private:

  void TransformFinalPath();

  multimap<double, pair<int,int>> edges_;

  vector<pair<int,int>> selected_edges_;

  unique_ptr<DisjointSet> disjoint_set_;

  unordered_map<int, int> node_degrees_;

};

} // namespace TSP
