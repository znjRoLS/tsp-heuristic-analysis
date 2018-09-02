//
// Created by rols on 9/2/2018.
//

#ifndef TSP_HEURISTICS_ANALYSIS_WORLD_GENERATOR_H
#define TSP_HEURISTICS_ANALYSIS_WORLD_GENERATOR_H

#include <memory>

#include "world.h"

using std::shared_ptr;

namespace TSP {
    class WorldGenerator {
    public:
        virtual shared_ptr<World> GenerateWorld(int n) = 0;
    };
};

#endif //TSP_HEURISTICS_ANALYSIS_WORLD_GENERATOR_H
