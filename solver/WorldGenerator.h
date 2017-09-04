//
// Created by Bojan Roško on 9/2/17.
//

#ifndef TSPHEURISTICANALYSIS_TSPWORLDGENERATOR_H
#define TSPHEURISTICANALYSIS_TSPWORLDGENERATOR_H

#include "Util.h"

namespace TSP {

  class WorldGenerator {
  public:
    virtual World GenerateWorld(int size) = 0;
  };

}


#endif //TSPHEURISTICANALYSIS_TSPWORLDGENERATOR_H
