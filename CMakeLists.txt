cmake_minimum_required(VERSION 3.16)
project(PATHFINDER_DSA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Raylib (already installed)
find_package(raylib REQUIRED)

# Collect ALL cpp files under src/
file(GLOB_RECURSE PROJECT_SOURCES
    src/*.cpp
)

# Create executable
add_executable(PATHFINDER_DSA ${PROJECT_SOURCES})

# Include src/ so headers like "graph/Graph.h" work
target_include_directories(PATHFINDER_DSA PRIVATE src)

# Link Raylib
target_link_libraries(PATHFINDER_DSA raylib)