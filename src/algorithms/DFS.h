#pragma once
#include "graph/Graph.h"
#include "PathResult.h"
#include "PathAlgorithm.h"

class DFS:public PathAlgorithm {
public:
     PathResult run(
        const Graph& graph,
        int start,
        int end
    ) override;
};
