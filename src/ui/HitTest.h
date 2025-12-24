#pragma once
#include "raylib.h"
#include "graph/Graph.h"
#include "core/Constants.h"

inline int getNodeUnderMouse(const Graph& graph) {
    Vector2 mouse = GetMousePosition();
    for (const Node& node : graph.nodes) {
        if (CheckCollisionPointCircle(mouse, node.position, NODE_RADIUS)) {
            return node.id;
        }
    }
    return -1;
}
/*
cd build
rm -rf *
cmake ..
make -j$(nproc)
./PathFinder-DSA
*/