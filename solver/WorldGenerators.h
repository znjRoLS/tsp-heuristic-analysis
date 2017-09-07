//
// Created by Bojan Roško on 9/2/17.
//

#ifndef TSPHEURISTICANALYSIS_GENERATORRANDOM_H
#define TSPHEURISTICANALYSIS_GENERATORRANDOM_H

#include "WorldGenerator.h"

#include <unordered_map>

#define REGISTER_WORLD_GENERATOR(x) \
struct x##_static_constructor { \
  public: x##_static_constructor() { \
    TSP::world_generator_container.insert({#x, new x()}); \
  } \
}; \
x##_static_constructor x##_hidden;


namespace TSP {

  class WorldGeneratorRandom : public WorldGenerator {
  public:
    World GenerateWorld(int size) override;
  };

}


#endif //TSPHEURISTICANALYSIS_GENERATORRANDOM_H
