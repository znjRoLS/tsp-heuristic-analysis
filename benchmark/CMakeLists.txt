file(GLOB SOURCES *.cc)
add_executable(tsp_benchmark ${SOURCES})
target_link_libraries(tsp_benchmark util)
target_link_libraries(tsp_benchmark tsp_solver)
