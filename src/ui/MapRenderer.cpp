#include "MapRenderer.h"
#include "raylib.h"
#include "core/Constants.h"

#include <algorithm> // std::find

void MapRenderer::draw(
    const Graph& graph,
    int hoveredNode,
    const PathResult& bfsResult,
    size_t bfsStep,
    int startNode,
    int endNode
) {
    /* -------------------- DRAW EDGES -------------------- */
    for (int i = 0; i < (int)graph.nodes.size(); ++i) {
        const Node& from = graph.nodes[i];

        for (const Edge& edge : graph.adjList[i]) {
            const Node& to = graph.nodes[edge.to];
            DrawLineEx(from.position, to.position, EDGE_THICKNESS, LIGHTGRAY);
        }
    }

    /* -------------------- DRAW NODES -------------------- */
    for (const Node& node : graph.nodes) {
        Color color = BLUE;

        /* -------- COLOR PRIORITY (TOP → BOTTOM) -------- */

        //  Final path (highest priority)
        if (!bfsResult.path.empty() &&
            std::find(bfsResult.path.begin(),
                      bfsResult.path.end(),
                      node.id) != bfsResult.path.end()) {
            color = ORANGE;
        }
        //  Start & End nodes
        else if (node.id == startNode) {
            color = GREEN;
        }
        else if (node.id == endNode) {
            color = RED;
        }
        // Animated BFS visited nodes
        else {
            for (size_t i = 0; i < bfsStep && i < bfsResult.visitedOrder.size(); ++i) {
                if (bfsResult.visitedOrder[i] == node.id) {
                    color = YELLOW;
                    break;
                }
            }
        }

        // Hover highlight (visual aid)
        if (node.id == hoveredNode) {
            color = PINK;
        }

        /* -------------------- RENDER -------------------- */
        DrawCircleV(node.position, NODE_RADIUS, color);

        DrawText(
            TextFormat("%d", node.id),
            node.position.x - 6,
            node.position.y - 6,
            12,
            WHITE
        );
    }
}
