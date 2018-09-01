#ifndef TSPHEURISTICANALYSIS_WORLD_H
#define TSPHEURISTICANALYSIS_WORLD_H

#include <memory>

#include "../util/matrix.h"
#include "../util/point2.h"

using std::shared_ptr;

namespace TSP {
    
    enum WorldType {
        ASSYMETRIC,
        SYMMETRIZSAC,
        EUCLIDIAN,
    };
    
    struct World {
        const WorldType world_type_;
        const shared_ptr<Matrix<Point2>> distances_;
    };
    
} // namespace TSP

#endif //TSPHEURISTICANALYSIS_WORLD_H
