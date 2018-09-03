#pragma once

#include <memory>

using std::shared_ptr;

#include "state.h"
#include "world_generator.h"

namespace TSP {

    struct SolverOptions {
        int world_size;
    };

    class Solver {
    public:

        Solver(SolverOptions options, shared_ptr<WorldGenerator> world_generator);

        void Reset();

    private:
        shared_ptr<SolverOptions> options_;
        shared_ptr<WorldGenerator> world_generator_;

        shared_ptr<State> state_;
    };

} // namespace TSP
