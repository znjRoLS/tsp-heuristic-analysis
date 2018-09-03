#pragma once

#include "algorithm.h"
#include "util.h"

namespace TSP {

    class ConstructiveAlgorithm : public Algorithm {
     public:
        explicit ConstructiveAlgorithm(shared_ptr<World> world);
        Path GetFinalPath();
    protected:
        Path current_path_;

        shared_ptr<World> world_;
    };

} // namespace TSP