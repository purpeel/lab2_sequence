cmake_minimum_required(VERSION 3.5)

project(lab2_tests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find GTest package
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

# Source files for tests
set(TEST_SOURCES
    main.cpp
)

# Create test executable
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
    ${CMAKE_THREAD_LIBS_INIT}
)

# Add test
add_test(NAME AllTests COMMAND run_tests)

# Enable testing
enable_testing()