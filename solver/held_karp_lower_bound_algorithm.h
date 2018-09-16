#pragma once

#include "lower_bound_algorithm.h"

namespace TSP {

class HeldKarpLowerBoundAlgorithm : public LowerBoundAlgorithm {
public:
    void Reset() override;
    bool Iterate(int granularity) override;
    int GetMaxGranularity() override;
};

} // namespace TSP
