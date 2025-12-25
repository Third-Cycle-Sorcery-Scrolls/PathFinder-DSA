#pragma once
#include "graph/Graph.h"
#include "PathResult.h"

class PathAlgorithm {
public:
    virtual ~PathAlgorithm() = default;

    virtual PathResult run(
        const Graph& graph,
        int start,
        int end
    ) = 0;
};
