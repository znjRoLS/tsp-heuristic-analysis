#pragma once

#include <memory>
#include "world.h"

using std::shared_ptr;

namespace TSP {

class Measure {
 public:
  virtual ~Measure();
  virtual shared_ptr<World> TransformMeasure(shared_ptr<World> world) = 0;
};

} // namespace TSP
