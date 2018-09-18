#pragma once

#include <memory>

#include "util.h"
#include "world.h"

namespace TSP {

/// Capturing current State (or current solution)
class State {
 public:
  explicit State(shared_ptr<World> world);

  State(shared_ptr<World> world, Path path);

  double CurrentPathCost();

  void UpdateOptimalPath(State state);

  const shared_ptr<World> world_;
  Path current_path_;

  static double PathCost(const Path& path, const shared_ptr<SquareMatrix<double>>& distances);

 private:
  void SetDefaultPath();
};
}
