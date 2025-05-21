cmake_minimum_required(VERSION 3.5)

project(lab2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add include directory to be available for all targets
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Add subdirectories
add_subdirectory(src/console)
add_subdirectory(src/ui)
add_subdirectory(tests)