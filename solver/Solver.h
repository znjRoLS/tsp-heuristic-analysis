//
// Created by Bojan Roško on 9/2/17.
//

#ifndef TSPHEURISTICANALYSIS_TSPSOLVER_H
#define TSPHEURISTICANALYSIS_TSPSOLVER_H

#include "Util.h"
#include "WorldGenerator.h"
#include "Algorithm.h"

#include <functional>
#include <unordered_map>

namespace TSP {

  struct SolverOptions {
    int world_size;
    int max_iterations;
  };

  class Solver {
  public:

    enum HandlerType{
      ON_START,
      ON_ITERATION,
      ON_FINISH
    };

    typedef function<void(const SharedState state)> StateHandler;

    Solver(SolverOptions options, WorldGenerator* world_generator, Algorithm* algorithm);

    // You can use to interfaces with this class
    // First one is to call Setup and Iterate until its done, and call GetState between
    // Second one is to register handlers to get called
    void Setup();
    bool Iterate();
    SharedState GetState();

    void ClearHandlers();
    void RegisterHandler(HandlerType handler_type, StateHandler func);
    void Solve();

  private:
    unique_ptr<WorldGenerator> world_generator;
    unique_ptr<Algorithm> algorithm;

    int world_size;
    int max_iterations;
    int current_iteration;

    SharedState state;

    unordered_map<int, vector<StateHandler>> handlers;
//    vector<StateHandler> handlers_start;
//    vector<StateHandler> handlers_iteration;
//    vector<StateHandler> handlers_finish;

    void CallAllHandlers(HandlerType handler_type);

  };

}


#endif //TSPHEURISTICANALYSIS_TSPSOLVER_H
