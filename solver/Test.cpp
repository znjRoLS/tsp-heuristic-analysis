//
// Created by Bojan Roško on 9/2/17.
//

#include "Solver.h"
#include "Algorithms.h"
#include "WorldGenerators.h"

using namespace TSP;

int main(int argc, char** argv) {

  unique_ptr<TSP::Solver> solver (new TSP::Solver({10, 10}, new WorldGeneratorRandom(), new AlgorithmBruteForce()));

  solver->RegisterHandler(Solver::ON_START, [] (SharedState state) {
    cout << "onstart:\n";
    cout << state;
  });

  solver->RegisterHandler(Solver::ON_ITERATION, [] (SharedState state) {
    cout << "oniteration:\n";
    cout << state;
  });

  solver->RegisterHandler(Solver::ON_FINISH, [] (SharedState state) {
    cout << "onfinish:\n";
    cout << state;
  });

  solver->Solve();

  return 0;
}