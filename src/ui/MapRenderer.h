#pragma once

#include "graph/Graph.h"
#include "algorithms/PathResult.h"
#include <cstddef> // for size_t

class MapRenderer {
public:
   void draw(
    const Graph& graph,
    int hoveredNode,
    const PathResult& result,
    size_t animationStep,
    int startNode,
    int endNode,
    size_t pathStep,
    bool pathAnimating
);

};
