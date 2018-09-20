#pragma once

#include <memory>
#include "measure.h"

using std::shared_ptr;

namespace TSP {

class AlfaImprovedMeasure : public Measure {
 public:
  shared_ptr<World> TransformMeasure(shared_ptr<World> world) override;

};

} // namespace TSP
