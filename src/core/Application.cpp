#include "Application.h"
#include "ui/HitTest.h"
#include "raylib.h"
#include <iostream>
#include "algorithms/AlgorithmFactory.h"
#include "ui/DrawAlgorithmMenu.h"

void Application::init() {
        //algorithm type
        algorithm = createAlgorithm(currentAlgorithm);
        // Initialize graph with nodes and edges

        graph.addNode({0,  {150, 150}, "Entoto"});
        graph.addNode({1,  {300, 120}, "Gullele"});
        graph.addNode({2,  {450, 160}, "Yeka"});
        graph.addNode({3,  {200, 300}, "Arat Kilo"});
        graph.addNode({4,  {350, 320}, "Sidist Kilo"});
        graph.addNode({5,  {150, 500}, "Kolfe"});
        graph.addNode({6,  {350, 520}, "Addis Ketema"});
        graph.addNode({7,  {500, 480}, "Merkato"});
        graph.addNode({8,  {600, 200}, "Bole"});
        graph.addNode({9,  {750, 140}, "Gerji"});
        graph.addNode({10, {900, 220}, "CMC"});
        graph.addNode({11, {650, 360}, "Mexico"});
        graph.addNode({12, {800, 380}, "Kazanchis"});
        graph.addNode({13, {950, 360}, "Ayat"});
        graph.addNode({14, {700, 550}, "Sarbet"});
        graph.addNode({15, {900, 550}, "Megenagna"});

        graph.addNode({16, {1050, 150}, "Summit"});
        graph.addNode({17, {1200, 300}, "Kotebe"});
        graph.addNode({18, {1100, 450}, "Gerji M."});
        graph.addNode({19, {1250, 550}, "Alem Bank"});
        graph.addNode({20, {1050, 700}, "Jemo"});
        graph.addNode({21, {850, 700}, "Gotera"});
        graph.addNode({22, {600, 700}, "Kality"});
        graph.addNode({23, {350, 700}, "Lafto"});

        // ===== LEFT ZONE CONNECTIONS =====
        graph.addEdge(0, 1, 1);
        graph.addEdge(1, 2, 1);
        graph.addEdge(0, 3, 1);
        graph.addEdge(3, 4, 1);
        graph.addEdge(4, 2, 1);

        graph.addEdge(3, 5, 1);
        graph.addEdge(5, 6, 1);
        graph.addEdge(6, 7, 1);
        graph.addEdge(4, 7, 1);

        // ===== LEFT → CENTER =====
        graph.addEdge(2, 8, 1);
        graph.addEdge(4, 11, 1);
        graph.addEdge(7, 11, 1);
        graph.addEdge(7, 14, 1);

        // ===== CENTER ZONE =====
        graph.addEdge(8, 9, 1);
        graph.addEdge(9, 10, 1);
        graph.addEdge(8, 11, 1);
        graph.addEdge(11, 12, 1);
        graph.addEdge(12, 13, 1);
        graph.addEdge(10, 13, 1);

        graph.addEdge(11, 14, 1);
        graph.addEdge(12, 15, 1);
        graph.addEdge(14, 15, 1);

        // ===== CENTER → RIGHT =====
        graph.addEdge(10, 16, 1);
        graph.addEdge(13, 17, 1);
        graph.addEdge(15, 18, 1);

        // ===== RIGHT ZONE =====
        graph.addEdge(16, 17, 1);
        graph.addEdge(17, 18, 1);
        graph.addEdge(18, 19, 1);
        graph.addEdge(18, 20, 1);
        graph.addEdge(19, 20, 1);

        // ===== BOTTOM LOOP (long alternative path) =====
        graph.addEdge(20, 21, 1);
        graph.addEdge(21, 22, 1);
        graph.addEdge(22, 23, 1);
        graph.addEdge(23, 5, 1);

        // ===== BACK CONNECTIONS (important for realism) =====
        graph.addEdge(14, 21, 1);
        graph.addEdge(6, 23, 1);
        graph.addEdge(9, 12, 1);
}

void Application::update() {
   float dt = GetFrameTime(); // time elapsed since last frame
   //dt is used for timing the Animation of BFS steps

    hoveredNode = getNodeUnderMouse(graph);
    // std::cout<<"Hovered Node: " << hoveredNode << std::endl;

    // Algorithm selection
    if (IsKeyPressed(KEY_ONE)) selectedAlgorithmIndex = 0;
    else if (IsKeyPressed(KEY_TWO)) selectedAlgorithmIndex = 1;
    else if (IsKeyPressed(KEY_THREE)) selectedAlgorithmIndex = 2;
    else if (IsKeyPressed(KEY_FOUR)) selectedAlgorithmIndex = 3;
    currentAlgorithm = algorithms[selectedAlgorithmIndex].type;
    algorithm = createAlgorithm(currentAlgorithm);

    if(currentAlgorithm !=algorithms[selectedAlgorithmIndex].type){
        //reset selections
        startNode = -1;
        endNode = -1;
        currentResult.path.clear();
        currentResult.visitedOrder.clear();
        algorithmDone = false;
        animationStep = 0;
        animationTimer = 0.0f;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int clickedNode = getNodeUnderMouse(graph);
        std::cout<<"Clicked Node: " << clickedNode << std::endl;
        if (clickedNode != -1) {
            if (startNode == -1) {
                startNode = clickedNode;
            } else if (endNode == -1) {
                endNode = clickedNode;
                // algorithm = algorithm::run(graph, startNode, endNode);
                currentResult = algorithm->run(graph, startNode, endNode);
                algorithmDone = true;
                animationStep = 0;
                animationTimer = 0.0f;
            } else {
                // reset start node if both already selected
                startNode = clickedNode;
                endNode = -1;
                currentResult.path.clear();
                currentResult.visitedOrder.clear();
                algorithmDone = false;
                animationStep = 0;
                animationTimer = 0.0f;
                // bfsResult.path.clear();
                // bfsResult.visitedOrder.clear();
                // bfsDone = false;
                // bfsStep = 0;
                // bfsTimer = 0.0f;
            }
        }
    }

    // Animate BFS traversal step by step
    if (algorithmDone && animationStep < currentResult.visitedOrder.size()) {
        animationTimer += dt;
        if (animationTimer >= animationDelay) {
            animationStep++;
            animationTimer = 0.0f;
        }
        //when exploration finished start path animation
        if(animationStep == currentResult.visitedOrder.size()){
            pathAnimating = true;
            pathStep = 0;
        }
    }
    //path animation
    if(pathAnimating && pathStep < currentResult.path.size()){
        animationTimer += dt;
        if (animationTimer >= animationDelay) {
            pathStep++;
            animationTimer = 0.0f;
        }
    }

    // Reset button (R)
    if (IsKeyPressed(KEY_R)) {
        startNode = -1;
        endNode = -1;
        currentResult.path.clear();
        currentResult.visitedOrder.clear();
        animationStep = 0;
        algorithmDone = false;
    }

}

void Application::render() {
   renderer.draw(
    graph,
    hoveredNode,
    currentResult,
    animationStep,
    startNode,
    endNode,
    pathStep,
    pathAnimating
);

    // DrawText("1 - BFS", 20, 20, 20, DARKGRAY);
    // DrawText("2 - DFS", 20, 45, 20, DARKGRAY);
    // DrawText("3 - Dijkstra", 20, 70, 20, DARKGRAY);

    // DrawText(
    //     TextFormat("Current: %s",
    //         currentAlgorithm == AlgorithmType::BFS ? "BFS" :
    //         currentAlgorithm == AlgorithmType::DFS ? "DFS" :
    //         "Dijkstra"
    //     ),
    //     20, 110, 20, MAROON
    // );
    DrawAlgorithmMenu(algorithms, selectedAlgorithmIndex);


}
