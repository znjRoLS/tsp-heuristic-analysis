//
// Created by Bojan Roško on 9/2/17.
//

#ifndef TSPHEURISTICANALYSIS_TSPSOLVER_H
#define TSPHEURISTICANALYSIS_TSPSOLVER_H

#include "Util.h"
#include "WorldGenerator.h"
#include "Algorithm.h"
#include "SolverCallback.h"

#include <functional>

namespace TSP {

  struct SolverOptions {
    int world_size;
    int max_iterations;
  };

  class Solver {
  public:


    Solver(SolverOptions options, WorldGenerator* world_generator, Algorithm* algorithm, shared_ptr<SolverCallbacks> solver_callbacks);

    // You can use to interfaces with this class
    // First one is to call Setup and Iterate until its done, and call GetState between
    // Second one is to register handlers to get called
    void Setup();
    bool Iterate();
    SharedState GetState();

    void Solve();

  private:
    shared_ptr<WorldGenerator> world_generator;
    shared_ptr<Algorithm> algorithm;
    shared_ptr<SolverCallbacks> solver_callbacks;

    int world_size;
    int max_iterations;
    int current_iteration;

    SharedState state;


  };

}


#endif //TSPHEURISTICANALYSIS_TSPSOLVER_H
