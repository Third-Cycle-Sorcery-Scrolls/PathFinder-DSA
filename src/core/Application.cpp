#include "Application.h"
#include "ui/HitTest.h"
#include "raylib.h"

void Application::init() {
    // Simple test graph
    graph.addNode({0, {200, 200}});
    graph.addNode({1, {400, 200}});
    graph.addNode({2, {600, 350}});
    graph.addNode({3, {400, 500}});
    graph.addNode({4, {200, 400}});//{vertex id, {x,y}}, x and y are positions on screen
    graph.addNode({5, {600, 150}});
    graph.addNode({6, {150, 150}});
    graph.addNode({7, {500, 450}});
    graph.addNode({8, {300, 300}});
    graph.addNode({9, {700, 400}});
    graph.addNode({10, {100, 500}});
    graph.addNode({11, {550, 100}});
    graph.addNode({12, {350, 550}});


    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 3, 1);
    graph.addEdge(0, 3, 1);
    graph.addEdge(0, 4, 1);
    graph.addEdge(4, 3, 1);
    graph.addEdge(1, 5, 1);
    graph.addEdge(0, 6, 1);
    graph.addEdge(3, 7, 1);
    graph.addEdge(4, 8, 1);
    graph.addEdge(8, 2, 1);
    graph.addEdge(5, 2, 1);
    graph.addEdge(6, 0, 1);
    graph.addEdge(7, 3, 1);
    graph.addEdge(8, 4, 1);
    graph.addEdge(9, 2, 1);
    graph.addEdge(10, 4, 1);
    graph.addEdge(11, 5, 1);
    graph.addEdge(12, 3, 1);
    graph.addEdge(12, 4, 1);
    graph.addEdge(8, 12, 1);
    graph.addEdge(7, 9, 1);
    graph.addEdge(1, 11, 1);
    graph.addEdge(6, 10, 1);
    graph.addEdge(10, 4, 1);
}

void Application::update() {
   float dt = GetFrameTime(); // time elapsed since last frame

    hoveredNode = getNodeUnderMouse(graph);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int clickedNode = getNodeUnderMouse(graph);
        if (clickedNode != -1) {
            if (startNode == -1) {
                startNode = clickedNode;
            } else if (endNode == -1) {
                endNode = clickedNode;
                bfsResult = BFS::run(graph, startNode, endNode);
                bfsDone = true;
                bfsStep = 0;
                bfsTimer = 0.0f;
            } else {
                // reset start node if both already selected
                startNode = clickedNode;
                endNode = -1;
                bfsResult.path.clear();
                bfsResult.visitedOrder.clear();
                bfsDone = false;
                bfsStep = 0;
                bfsTimer = 0.0f;
            }
        }
    }

    // Animate BFS traversal step by step
    if (bfsDone && bfsStep < bfsResult.visitedOrder.size()) {
        bfsTimer += dt;
        if (bfsTimer >= bfsDelay) {
            bfsStep++;
            bfsTimer = 0.0f;
        }
    }

    // Reset button (R)
    if (IsKeyPressed(KEY_R)) {
        startNode = -1;
        endNode = -1;
        bfsResult.path.clear();
        bfsResult.visitedOrder.clear();
        bfsStep = 0;
        bfsDone = false;
    }

}

void Application::render() {
   renderer.draw(
    graph,
    hoveredNode,
    bfsResult,
    bfsStep,
    startNode,
    endNode
);

}
