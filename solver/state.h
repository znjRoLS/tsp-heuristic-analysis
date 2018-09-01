#ifndef TSPHEURISTICANALYSIS_STATE_H
#define TSPHEURISTICANALYSIS_STATE_H

#include <memory>

#include "util.h"
#include "world.h"

namespace TSP {
    struct State {
        double CurrentCost();

        const shared_ptr<World> world_;
        Path current_path_;
    };
}

#endif //TSPHEURISTICANALYSIS_STATE_H
