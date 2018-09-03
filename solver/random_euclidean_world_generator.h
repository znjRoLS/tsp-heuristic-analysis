//
// Created by rols on 9/3/2018.
//

#ifndef TSP_HEURISTICS_ANALYSIS_RANDOM_EUCLIDEAN_WORLD_GENERATOR_H
#define TSP_HEURISTICS_ANALYSIS_RANDOM_EUCLIDEAN_WORLD_GENERATOR_H

#include "euclidean_world_generator.h"

namespace TSP {
    class RandomEuclideanWorldGenerator: public EuclideanWorldGenerator {
    public:
        vector<Point2> GenerateNodes(int n) override;
    };
} // namespace TSP


#endif //TSP_HEURISTICS_ANALYSIS_RANDOM_EUCLIDEAN_WORLD_GENERATOR_H
