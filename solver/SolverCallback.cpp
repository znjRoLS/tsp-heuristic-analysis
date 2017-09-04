//
// Created by Bojan Roško on 9/4/17.
//

#include "SolverCallback.h"

namespace TSP {

  SolverCallbacks::SolverCallbacks() {

    callbacks.insert({ON_START, {}});
    callbacks.insert({ON_ITERATION, {}});
    callbacks.insert({ON_FINISH, {}});
  }


  void SolverCallbacks::ClearHandlers() {
    for(auto& key_pair : callbacks) {
      key_pair.second.clear();
    }
  }

  void SolverCallbacks::RegisterHandler(CallbackType handler_type, SolverCallback func) {
    callbacks[handler_type].push_back(func);
  }

  void SolverCallbacks::CallAllHandlers(CallbackType handler_type, SharedState& state) {
    for (SolverCallback handler: callbacks[handler_type]) {
      handler(state);
    }
  }

}