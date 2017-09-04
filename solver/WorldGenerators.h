//
// Created by Bojan Roško on 9/2/17.
//

#ifndef TSPHEURISTICANALYSIS_GENERATORRANDOM_H
#define TSPHEURISTICANALYSIS_GENERATORRANDOM_H

#include "WorldGenerator.h"

namespace TSP {

  class WorldGeneratorRandom : public WorldGenerator {
  public:
    World GenerateWorld(int size) override;
  };

}


#endif //TSPHEURISTICANALYSIS_GENERATORRANDOM_H
