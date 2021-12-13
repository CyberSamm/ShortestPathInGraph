cmake_minimum_required(VERSION 3.5)

project(ShortPath)

add_executable(dijkstra src/dijkstra.cpp)
add_executable(cycle src/cycle.cpp)
add_executable(matrix src/matrix.cpp)

add_executable(rand src/randVertices.cpp)