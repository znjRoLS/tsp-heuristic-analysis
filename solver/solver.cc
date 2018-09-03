#include <memory>

using std::make_shared;

#include "solver.h"

namespace TSP {

    Solver::Solver(TSP::SolverOptions options, shared_ptr<TSP::WorldGenerator> world_generator) {

    }

    void Solver::Reset() {
        state_ = make_shared<State>(world_generator_->GenerateWorld(options_->world_size));
    }

} // namespace TSP
