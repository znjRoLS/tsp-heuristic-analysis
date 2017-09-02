//
// Created by Bojan Roško on 9/2/17.
//

#ifndef TSPHEURISTICANALYSIS_TSPWORLDGENERATOR_H
#define TSPHEURISTICANALYSIS_TSPWORLDGENERATOR_H

#include <memory>
#include <vector>
#include <utility>

using namespace std;

class TSPWorldGenerator {
public:
  virtual unique_ptr<vector<pair<double,double>>> GenerateWorld(int size) = 0;
};


#endif //TSPHEURISTICANALYSIS_TSPWORLDGENERATOR_H
