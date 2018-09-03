cmake_minimum_required (VERSION 2.6)
add_definitions(-std=gnu++17)

project (tsp_heuristics_analysis)

set(tsp_heuristics_analysis_VERSION_MAJOR 0)
set(tsp_heuristics_analysis_VERSION_MINOR 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall")

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (EXISTS googletest)
    set(GTEST_USE TRUE)
else()
    set(GTEST_USE FALSE)
endif()

if (GTEST_USE)
    include_directories(googletest/googletest/include)
    add_subdirectory (googletest/googletest)
    enable_testing()
endif()

# Add util so it can be used by tsp_solver
include_directories("util")
add_subdirectory(util)

add_subdirectory(solver)
