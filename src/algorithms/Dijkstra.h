#pragma once
#include "../graph/Graph.h"
#include "PathResult.h"
#include "PathAlgorithm.h"

class Dijkstra : public PathAlgorithm {
public:
    PathResult run(const Graph& graph, int start, int end) override;
};
