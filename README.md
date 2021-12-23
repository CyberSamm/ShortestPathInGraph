# ShortestPathInGraph

## Task:
Given a positive weighted directed graph, find the shortest paths between two nodes in a graph.
Tests: 
1) cycle contains 10000 vertices
2) 100 X 100 matrix 

## Realization:

The project contains **scripts** and **CMakeLists.txt** both are for building and running cpp programs. cpp files are stored in the **src/** directory. The **Tests/** directory contains tests. The **io/** directory is for input output files.

### src
* *dijkstra.cpp* takes graph from input.txt and writes number of paths, path length, and paths to output.txt. input.txt and output.txt are in io/ directory.
* *cycle.cpp* white to input.txt adjacency list representation of graph(cycle contains 10000 vertices).
* *cycle.cpp* white to input.txt adjacency list representation of graph(100 X 100 matrix).

### Tests
* *cycle_test.cpp* checks the work of the dijkstra.cpp that found paths for the cycle.
* *martix_test.cpp* checks the work of the dijkstra.cpp that found paths for the matrix.
* *randVertices.cpp* generate random naumbers and whites them to random.txt. random.txt is in io/ directory. 

### io
* *input.txt* contains graph. Graph represented by adjacency list.
* *output.txt* contains result of dijkstra algorithm work.
* *random.txt* contains a sequence of pairs of random numbers that are start and destination vertices. The *random.txt* is needed for testing.

### scripts
* *build.sh* script makes build directory, calls cmake and makes executable files. 
* *clean.sh* script deletes files created during building.
* *run.sh* script runs the executable file whose name is in the script argument.
* *test.sh* script tests project work.

