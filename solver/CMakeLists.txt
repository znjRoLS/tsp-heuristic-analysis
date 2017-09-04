
file(GLOB TSP_SOURCES
        Util.*
        WorldGenerator*
        Algorithm*
        Solver.*
        SolverCallback.*
        State.*
        )

add_library(TSPState ${TSP_SOURCES})

add_executable(TSPTester Test.cpp)
target_link_libraries(TSPTester TSPState)