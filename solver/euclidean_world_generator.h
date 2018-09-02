//
// Created by rols on 9/2/2018.
//

#ifndef TSP_HEURISTICS_ANALYSIS_EUCLIDEAN_WORLD_GENERATOR_H
#define TSP_HEURISTICS_ANALYSIS_EUCLIDEAN_WORLD_GENERATOR_H

#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;

#include "point2.h"
#include "world.h"
#include "world_generator.h"

namespace TSP {
    class EuclideanWorldGenerator: public WorldGenerator {
    public:
        virtual vector<Point2> GenerateNodes(int n) = 0;

        shared_ptr<World> GenerateWorld(int n) override;
    };
}

#endif //TSP_HEURISTICS_ANALYSIS_EUCLIDEAN_WORLD_GENERATOR_H
