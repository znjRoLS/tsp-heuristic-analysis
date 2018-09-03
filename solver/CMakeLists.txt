file (GLOB SOURCES *.cc)

add_library(tsp_solver ${SOURCES})
target_link_libraries(tsp_solver util)

add_executable(tsp_test test.cc)
target_link_libraries(tsp_test tsp_solver)

if (GTEST_USE)
    file( GLOB TEST_SOURCES test/*_test.cc )
    foreach ( testsourcefile ${TEST_SOURCES})
        get_filename_component( testname_cc ${testsourcefile} NAME )
        string( REPLACE "_test" "" testtarget ${testname_cc} )
        string( REPLACE ".cc" "" testname ${testname_cc} )
        cxx_test(${testname} gtest_main ${testtarget})
        target_link_libraries(${testname} tsp_solver)
    endforeach()
endif()
