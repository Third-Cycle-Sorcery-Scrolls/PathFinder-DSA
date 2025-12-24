#include "Graph.h"
#include "BFS.h"
#include "PathResult.h"
#include <iostream>
void testBFS(){

    Graph g;

    g.addNode({0, {0, 0}});
    g.addNode({1, {100, 0}});//id:1, position:(100,0)
    g.addNode({2, {200, 0}});//id:2, position
    g.addNode({3, {0, 100}});//id:3, position:(0,100)
    g.addNode({4, {100, 100}});//id:4, position
    g.addNode({5, {200, 100}});//id:5, position:(200,100)
    // Create edges
    g.addEdge(0, 1, 1.0);// Edge from node 0 to 1
    g.addEdge(1, 2, 1.0);// Edge from node 1 to 2
    g.addEdge(0, 3, 1.0);// Edge from node 0 to 3
    g.addEdge(1, 4, 1.0);// Edge from node 1 to 4
    g.addEdge(2, 5, 1.0);// Edge from node 2 to 5
    g.addEdge(3, 4, 1.0);// Edge from node 3 to 4
    g.addEdge(4, 5, 1.0);// Edge from node 4 to 5
    // Perform BFS from node 0 to node 5
    BFS bfs;
    PathResult result = bfs.findPath(g, 0, 5);
    // Expected path: 0 -> 1 -> 2 -> 5 or 0 -> 3 -> 4 -> 5
    // Print the path
    for (int nodeId : result.path) {
        std::cout << nodeId << " ";
    }
    //execution command with all the necessary includes and using namespace std
    //g++ -std=c++17 -I./src -o test_BFS tests/test_BFS.cpp src/graph/Graph.cpp src/algorithms/BFS.cpp src/graph/Edge.cpp src/graph/Node.cpp
}