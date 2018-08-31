//
// Created by Bojan Roško on 9/4/17.
//

#ifndef TSPHEURISTICANALYSIS_SOLVERCALLBACK_H
#define TSPHEURISTICANALYSIS_SOLVERCALLBACK_H

#include "State.h"

#include <unordered_map>

namespace  TSP{

class SolverCallbacks {
public:

  SolverCallbacks();

  enum CallbackType{
    ON_START,
    ON_ITERATION,
    ON_FINISH
  };

  typedef function<void(const SharedState state)> SolverCallback;

  void ClearHandlers();
  void RegisterHandler(CallbackType callback_type, SolverCallback func);


  unordered_map<int, vector<SolverCallback>> callbacks;

  void CallAllHandlers(CallbackType handler_type, SharedState& state);

};

}


#endif //TSPHEURISTICANALYSIS_SOLVERCALLBACK_H
