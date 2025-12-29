#include "MapRenderer.h"
#include "raylib.h"
#include "core/Constants.h"

void MapRenderer::draw(
    const Graph& graph,
    int hoveredNode,
    const PathResult& result,
    size_t animationStep,
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
        bool isColored = false;

        /* -------- COLOR PRIORITY (TOP → BOTTOM) -------- */

        // Start node
        if (node.id == startNode) {
            color = GREEN;
            isColored = true;
        }
        // End node
        else if (node.id == endNode) {
            color = RED;
            isColored = true;
        }
        // Animated path (only show up to pathStep)
        else if (pathAnimating) {
            for (size_t i = 0; i < pathStep && i < result.path.size(); ++i) {
                if (result.path[i] == node.id) {
                    color = ORANGE;
                    isColored = true;
                    break;
                }
            }
        }

        // Animated visited nodes (always show visited, path overrides with orange)
        if (!isColored) {
            for (size_t i = 0;
                 i < animationStep && i < result.visitedOrder.size();
                 ++i) {
                if (result.visitedOrder[i] == node.id) {
                    color = YELLOW;
                    isColored = true;
                    break;
                }
            }
        }

        // Hover highlight (always visible, overrides)
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
