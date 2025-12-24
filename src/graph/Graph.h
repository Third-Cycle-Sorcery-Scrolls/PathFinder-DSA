#pragma once

#include <vector>
#include "Node.h"
#include "Edge.h"


class Graph {
public:
    std::vector<Node> nodes;
    std::vector<std::vector<Edge>> adjList;

    void addNode(const Node& node);
    void addEdge(int from, int to, double weight,bool bidirectional = true);


};