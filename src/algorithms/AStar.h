#pragma once
#include "../graph/Graph.h"
#include "PathResult.h"

class AStar {
public:
    static PathResult run(const Graph& graph, int start, int end);
private:
    static float heuristic(const Graph& graph, int a, int b);
};
