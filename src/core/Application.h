// #pragma once
// #include "../graph/Graph.h"
#include "../graph/Graph.h"
#include "../ui/MapRenderer.h"
// #include "ui/MapRenderer.h"
#include "../algorithms/BFS.h"

class Application {
public:
    void init();
    void update();
    void render();

private:
    Graph graph;
    MapRenderer renderer;
    int hoveredNode = -1;

    int startNode = -1;
    int endNode = -1;
    PathResult bfsResult;
    bool bfsDone = false;
    size_t bfsStep = 0;  // current step of BFS animation
    float bfsDelay = 0.1f; // delay between steps in seconds
    float bfsTimer = 0.0f;
};
