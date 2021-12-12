cmake_minimum_required(VERSION 3.5)

project(ShortPath)

add_executable(dijkstra src/dijkstra.cpp)
add_executable(cycle src/create_cycle.cpp)
add_executable(matrix src/create_matrix.cpp)

add_executable(cycle_test tests/cycle_test.cpp)
add_executable(matrix_test tests/matrix_test.cpp)

add_executable(rand tests/rand.cpp)