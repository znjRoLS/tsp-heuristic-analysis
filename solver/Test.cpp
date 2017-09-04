//
// Created by Bojan Roško on 9/2/17.
//

#include "Solver.h"
#include "Algorithms.h"
#include "WorldGenerators.h"

using namespace TSP;

int main(int argc, char** argv) {

  shared_ptr<SolverCallbacks> callbacks (new SolverCallbacks);

  callbacks->RegisterHandler(SolverCallbacks::ON_START, [] (SharedState state) {
    cout << "onstart:\n";
    cout << state;
  });

  callbacks->RegisterHandler(SolverCallbacks::ON_ITERATION, [] (SharedState state) {
    cout << "oniteration:\n";
    cout << state;
  });

  callbacks->RegisterHandler(SolverCallbacks::ON_FINISH, [] (SharedState state) {
    cout << "onfinish:\n";
    cout << state;
  });

  cout << "Test 1" << endl;

  unique_ptr<TSP::Solver> solver (new TSP::Solver({10, 10}, new WorldGeneratorRandom(), new AlgorithmBruteForce(), callbacks));

  solver->Solve();

  cout << "Test 2" << endl;

  solver = unique_ptr<TSP::Solver>(new TSP::Solver({3, 1000}, new WorldGeneratorRandom(), new AlgorithmBruteForce(), callbacks));

  solver->Solve();



  return 0;
}