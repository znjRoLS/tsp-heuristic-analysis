//
// Created by Bojan Roško on 9/2/17.
//

#ifndef TSPHEURISTICANALYSIS_TSPWORLDGENERATOR_H
#define TSPHEURISTICANALYSIS_TSPWORLDGENERATOR_H

#include "Util.h"

#include <unordered_map>

namespace TSP {


  class WorldGenerator {
  public:
    virtual World GenerateWorld(int size) = 0;
  };

  extern unordered_map<string, WorldGenerator*> world_generator_container;

}


#endif //TSPHEURISTICANALYSIS_TSPWORLDGENERATOR_H
