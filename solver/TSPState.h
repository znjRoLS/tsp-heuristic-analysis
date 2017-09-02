//
// Created by Bojan Roško on 9/2/17.
//

#ifndef TSPHEURISTICANALYSIS_TSPSTATE_H
#define TSPHEURISTICANALYSIS_TSPSTATE_H

#include <vector>
#include <memory>
#include <utility>

#include "TSPWorldGenerator.h"

using namespace std;

struct StateOptions {
  int size;
};

class TSPState {
public:
  explicit TSPState(TSPWorldGenerator* generator, StateOptions& options);
  ~TSPState();

  void GenerateNewWorld();

  double GetCost(int i, int j);

  vector<int> GetPath();
  void SetPath(vector<int>& new_path);

  vector<pair<double,double>>* GetNodes();

private:

  int size;
  unique_ptr<TSPWorldGenerator> generator;

  shared_ptr<vector<pair<double,double>>> nodes;
  vector<int> path;
};


#endif //TSPHEURISTICANALYSIS_TSPSTATE_H
