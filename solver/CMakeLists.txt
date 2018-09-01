
add_library(tsp_solver
        state.cpp
        )

target_include_directories(tsp_solver PUBLIC util)

add_executable(tsp_test test.cpp)
target_link_libraries(tsp_test tsp_solver)