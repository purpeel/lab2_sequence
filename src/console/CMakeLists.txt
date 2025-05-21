cmake_minimum_required(VERSION 3.5)

project(console_app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    main.cpp
)

# Create executable
add_executable(console_app ${SOURCES})

# Include directories
target_include_directories(console_app PRIVATE 
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/src/tmpl
)

# Install
install(TARGETS console_app
    RUNTIME DESTINATION bin
)