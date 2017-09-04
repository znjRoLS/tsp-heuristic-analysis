//
// Created by Bojan Roško on 9/2/17.
//

#include "Solver.h"

namespace TSP{
  Solver::Solver(SolverOptions options, WorldGenerator *arg_world_generator, Algorithm *arg_algorithm):
      world_size(options.world_size),
      max_iterations(options.max_iterations),
      world_generator(arg_world_generator),
      algorithm(arg_algorithm),
      state(new State()){

    handlers.insert({ON_START, {}});
    handlers.insert({ON_ITERATION, {}});
    handlers.insert({ON_FINISH, {}});
  }

  void Solver::ClearHandlers() {
//    handlers_start.clear();
//    handlers_iteration.clear();
//    handlers_finish.clear();
    for(auto& key_pair : handlers) {
      key_pair.second.clear();
    }
  }

  void Solver::RegisterHandler(HandlerType handler_type, StateHandler func) {
    handlers[handler_type].push_back(func);
  }

  void Solver::Solve() {

    Setup();
    CallAllHandlers(ON_START);

    while(Iterate()) {
      CallAllHandlers(ON_ITERATION);
    }

    CallAllHandlers(ON_FINISH);
  }

  void Solver::CallAllHandlers(HandlerType handler_type) {
    for (StateHandler handler: handlers[handler_type]) {
      handler(state);
    }
  }

  void Solver::Setup() {
    state->world = world_generator->GenerateWorld(world_size);
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