#pragma once
#include "../graph/Graph.h"
#include "PathResult.h"
#include "PathAlgorithm.h"
/*
BFS: Breadth-First Search algorithm implementation
Inherits from PathAlgorithm and implements the run method to perform BFS on the given graph
from a start node to an end node.

*/
class BFS : public PathAlgorithm {
public:
    PathResult run(const Graph& graph, int start, int end) override;
};
