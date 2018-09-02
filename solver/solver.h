//
// Created by rols on 9/2/2018.
//

#ifndef TSP_HEURISTICS_ANALYSIS_SOLVER_H
#define TSP_HEURISTICS_ANALYSIS_SOLVER_H

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


#endif //TSP_HEURISTICS_ANALYSIS_SOLVER_H
