#pragma once

#include "measure.h"

namespace TSP {

class ClassicMeasure : public Measure {
 public:
  shared_ptr<World> TransformMeasure(shared_ptr<World> world);
};

} // namespace TSP
