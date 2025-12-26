#pragma once
#include "../graph/Graph.h"
#include "PathResult.h"

class Dijkstra {
public:
    static PathResult run(const Graph& graph, int start, int end);
};
