#pragma once

#include "graph/Graph.h"
#include "algorithms/PathResult.h"
#include <cstddef> // for size_t

class MapRenderer {
public:
    void draw(
        const Graph& graph,
        int hoveredNode,
        const PathResult& bfsResult,
        size_t bfsStep,
        int startNode,
        int endNode
    );
};
