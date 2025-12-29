#pragma once
#include "../graph/Graph.h"
#include "PathResult.h"
#include "PathAlgorithm.h"

class AStar : public PathAlgorithm {
public:
    PathResult run(const Graph& graph, int start, int end) override;
private:
    static float heuristic(const Graph& graph, int a, int b);
};
