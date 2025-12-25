#pragma once
#include "graph/Graph.h"
#include "ui/MapRenderer.h"
#include "algorithms/BFS.h"
#include "AlgorithmType.h"
#include "algorithms/PathAlgorithm.h"
#include "algorithms/PathResult.h"
#include <memory>
#include "AlgorithmInfo.h"
#include <vector>

class Application {
public:
    void init();
    void update();
    void render();

private:
    Graph graph;
    MapRenderer renderer;
    int hoveredNode = -1;

    AlgorithmType currentAlgorithm = AlgorithmType::BFS;
    std::unique_ptr<PathAlgorithm> algorithm;
    PathResult currentResult;

    int startNode = -1;
    int endNode = -1;
    bool algorithmDone = false;
    size_t animationStep = 0;  // current step of animation
    float animationDelay = 0.1f; // delay between steps in seconds
    float animationTimer = 0.0f; // timer to track time elapsed for animation
    size_t pathStep = 0;
    bool pathAnimating = false;

    //algorithm info
    std::vector<AlgorithmInfo> algorithms = {
        {AlgorithmType::BFS, "Breadth-First Search"},
        {AlgorithmType::DFS, "Depth-First Search"},
        {AlgorithmType::DIJKSTRA, "Dijkstra's Algorithm"},
        {AlgorithmType::ASTAR, "A* Search Algorithm"}
    };
    int selectedAlgorithmIndex = 0;

    
    // PathResult bfsResult;
    // bool bfsDone = false;
    // size_t bfsStep = 0;  // current step of BFS animation
    // float bfsDelay = 0.1f; // delay between steps in seconds
    // float bfsTimer = 0.0f; // timer to track time elapsed for BFS animation
};
