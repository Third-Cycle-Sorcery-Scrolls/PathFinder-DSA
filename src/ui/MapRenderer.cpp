#include "MapRenderer.h"
#include "raylib.h"
#include "core/Constants.h"

void MapRenderer::draw(
    const Graph& graph,
    int hoveredNode,
    const PathResult& result,
    size_t bfsStep,
    int startNode,
    int endNode,
    size_t pathStep,
    bool pathAnimating
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

        // Start node
        if (node.id == startNode) {
            color = GREEN;
        }
        // End node
        else if (node.id == endNode) {
            color = RED;
        }
        // Animated path (only show up to pathStep)
        else if (pathAnimating) {
            for (size_t i = 0; i < pathStep && i < result.path.size(); ++i) {
                if (result.path[i] == node.id) {
                    color = ORANGE;
                    break;
                }
            }
        }
        // Animated visited nodes
        else {
            for (size_t i = 0;
                 i < bfsStep && i < result.visitedOrder.size();
                 ++i) {
                if (result.visitedOrder[i] == node.id) {
                    color = YELLOW;
                    break;
                }
            }
        }

        // 5️⃣ Hover highlight (always visible)
        if (node.id == hoveredNode) {
            color = PINK;
        }

        /* -------------------- RENDER NODE -------------------- */
        DrawCircleV(node.position, NODE_RADIUS, color);

        /* -------------------- DRAW LABEL -------------------- */
        const char* label = node.label.c_str();
        int fontSize = 18;
        int textWidth = MeasureText(label, fontSize);

        DrawText(
            label,
            node.position.x - textWidth / 2,
            node.position.y - fontSize / 2,
            fontSize,
            BLACK
        );
    }
}
