//
// Created by Bojan Roško on 9/2/17.
//

#include "Solver.h"

namespace TSP{
  Solver::Solver(SolverOptions options, WorldGenerator *arg_world_generator, Algorithm *arg_algorithm, shared_ptr<SolverCallbacks> arg_solver_callbacks):
      world_generator(arg_world_generator),
      algorithm(arg_algorithm),
      solver_callbacks(arg_solver_callbacks),
      world_size(options.world_size),
      max_iterations(options.max_iterations),
      state(nullptr){

  }

  void Solver::Solve() {

    Setup();
    solver_callbacks->CallAllHandlers(SolverCallbacks::ON_START, state);

    while(Iterate()) {
      solver_callbacks->CallAllHandlers(SolverCallbacks::ON_ITERATION, state);
    }

    solver_callbacks->CallAllHandlers(SolverCallbacks::ON_FINISH, state);
  }

  void Solver::Setup() {
    state = SharedState(new State(world_generator->GenerateWorld(world_size)));
    algorithm->Setup(state);
    current_iteration = 0;

  }

  bool Solver::Iterate() {
    if (current_iteration >= max_iterations) {
      return false;
    }

    current_iteration++;

    return algorithm->Iterate();
  }

  SharedState Solver::GetState() {
    return state;
  }

}