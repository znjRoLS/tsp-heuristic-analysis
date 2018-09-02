#ifndef TSPHEURISTICANALYSIS_WORLD_H
#define TSPHEURISTICANALYSIS_WORLD_H

#include <memory>

#include "matrix.h"
#include "point2.h"

using std::shared_ptr;

namespace TSP {
    
    enum WorldType {
        ASSYMETRIC,
        SYMMETRIZSAC,
        EUCLIDEAN,
    };
    
    struct World {
        const int size;
        const WorldType world_type_;
        const shared_ptr<Matrix<double>> distances_;
    };
    
} // namespace TSP

#endif //TSPHEURISTICANALYSIS_WORLD_H
