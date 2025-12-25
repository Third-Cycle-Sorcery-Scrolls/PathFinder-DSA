#pragma once
#include "../graph/Graph.h"
#include "PathResult.h"

class DFS {
public:
    static PathResult findPath(
        const Graph& graph,
        int start,
        int goal
    );
};
