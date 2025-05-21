cmake_minimum_required(VERSION 3.5)

project(tests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find GTest package (you may need to install it)
find_package(GTest QUIET)

if(GTest_FOUND)
    # Source files for tests
    set(TEST_SOURCES
        # Add your test source files here
        # For example: test_dynamic_array.cpp
    )

    # Create test executable
    if(TEST_SOURCES)
        add_executable(run_tests ${TEST_SOURCES})
        
        # Include directories
        target_include_directories(run_tests PRIVATE 
            ${CMAKE_SOURCE_DIR}/inc
            ${CMAKE_SOURCE_DIR}/src/tmpl
            ${GTEST_INCLUDE_DIRS}
        )
        
        # Link libraries
        target_link_libraries(run_tests PRIVATE 
            ${GTEST_BOTH_LIBRARIES}
            pthread
        )
        
        # Add test
        add_test(NAME AllTests COMMAND run_tests)
        
        # Enable testing
        enable_testing()
    else()
        message(STATUS "No test sources found. Tests will not be built.")
    endif()
else()
    message(STATUS "GTest not found. Tests will not be built.")
endif()