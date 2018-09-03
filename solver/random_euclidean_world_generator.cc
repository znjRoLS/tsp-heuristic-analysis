//
// Created by rols on 9/3/2018.
//

#include "random.h"
#include "util.h"

#include "random_euclidean_world_generator.h"

namespace TSP {

    vector<Point2> RandomEuclideanWorldGenerator::GenerateNodes(int n) {
        vector<Point2> nodes((uint)n);

        for (int i = 0 ; i < n ; i ++) {
            nodes[i] = {Random::GetDouble(), Random::GetDouble()};
        }

        return nodes;
    }

} // namespace TSP