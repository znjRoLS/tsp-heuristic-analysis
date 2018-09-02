#ifndef TSPHEURISTICANALYSIS_UTIL_H
#define TSPHEURISTICANALYSIS_UTIL_H

#include <vector>
#include <cassert>

#define ASSERT(x) assert(x);
#define ASSERT_EQ(x,y) ASSERT(x == y)

namespace TSP {

    /// Path type representing a solution Path in TSP
    typedef std::vector<int> Path;

} // namespace TSP

#endif //TSPHEURISTICANALYSIS_UTIL_H
