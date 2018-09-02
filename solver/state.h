#ifndef TSPHEURISTICANALYSIS_STATE_H
#define TSPHEURISTICANALYSIS_STATE_H

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

    private:
        void SetDefaultPath();

        const shared_ptr<World> world_;
        Path current_path_;
    };
}

#endif //TSPHEURISTICANALYSIS_STATE_H
