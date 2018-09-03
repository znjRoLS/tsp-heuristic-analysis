#pragma once

#include <memory>
#include <unordered_set>

using std::shared_ptr;
using std::unordered_set;

#include "constructive_algorithm.h"
#include "world.h"
#include "util.h"

namespace TSP {

class RandomConstructiveAlgorithm : public ConstructiveAlgorithm {
 public:
  explicit RandomConstructiveAlgorithm(shared_ptr<World> world);
  void Reset() override;
  bool Iterate(int granularity) override;
  int GetMaxGranularity() override;

 private:
  unordered_set<int> unvisited_;
  Path random_path_;
};

} // namespace TSP
