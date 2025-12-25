#include "./raylib/include/raylib.h"
#include <cmath>
#include <limits>
#include <queue>
#include <stack>
#include <vector>

/*
To compile
g++ maze.cpp -I./raylib/include -L./raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -o maze.exe
*/
// --- GRAPH THEORY CONSTANTS ---
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int COLS = 40; // Number of Nodes Horizontally
const int ROWS = 40; // Number of Nodes Vertically
const int CELL_WIDTH = SCREEN_WIDTH / COLS;
const int CELL_HEIGHT = SCREEN_HEIGHT / ROWS;
const int INF = std::numeric_limits<int>::max();

// --- NODE STRUCTURE (The "Vertex" in Graph Theory) ---
struct Node {
    int x, y;     // Grid Position
    bool isWall;  // If true, no Edges connect to this Node
    bool visited; // Has the algorithm processed this Node?
    int distance; // Distance from Start Node (Graph Weight)
    Node *parent; // Pointer to previous Node (to reconstruct path)

    // Helper to draw the node
    void Draw(Color color) {
        DrawRectangle(x * CELL_WIDTH, y * CELL_HEIGHT, CELL_WIDTH - 1, CELL_HEIGHT - 1, color);
    }
};

// --- GLOBAL STATE ---
std::vector<std::vector<Node>> grid(ROWS, std::vector<Node>(COLS));
Node *startNode;
Node *endNode;

// Priority Queue for Dijkstra: Stores pair <Distance, Node*>
// Orders nodes so the one with the smallest distance is processed first
using PQElement = std::pair<int, Node *>;
std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> pq;

bool algorithmRunning = false;
bool pathFound = false;
bool statsComputed = false; // avoid recomputing overlay stats every frame
int visitedCount = 0;
int pathLengthDisplay = 0;

// --- INITIALIZATION ---
void InitGrid() {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            grid[y][x].x = x;
            grid[y][x].y = y;
            grid[y][x].isWall = false;
            grid[y][x].visited = false;
            grid[y][x].distance = INF;
            grid[y][x].parent = nullptr;
        }
    }

    // Set fixed Start and End points
    startNode = &grid[5][5];
    endNode = &grid[35][35];

    // Setup Start Node
    startNode->distance = 0;

    // Clear Queue and add start
    pq = std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>>();
    pq.push({0, startNode});

    algorithmRunning = false;
    pathFound = false;
    statsComputed = false;
    visitedCount = 0;
    pathLengthDisplay = 0;
}

int ComputePathLength() {
    int length = 1; // Start with 1 to include the end node
    Node *curr = endNode;

    // Count nodes in path from end back to start via parent links
    while (curr != nullptr && curr != startNode) {
        if (curr->parent == nullptr)
            break;
        length++;
        curr = curr->parent;
    }
    return length;
}

// --- DIJKSTRA STEP (Graph Traversal) ---
// We run this once per frame to create the visual animation
void UpdateDijkstra() {
    if (pq.empty() || pathFound)
        return;

    // 1. Get the node with the smallest distance
    Node *current = pq.top().second;
    pq.pop();
    
     if (current->visited)
        return; // Skip if already processed
    current->visited = true;
    visitedCount++;

    // If we reached the end, stop
    if (current == endNode) {
        pathFound = true;
        if (!statsComputed) {
            pathLengthDisplay = ComputePathLength();
            statsComputed = true;
        }
        return;
    }

    // 2. Check Edges (Neighbors: Up, Down, Left, Right)
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    for (int i = 0; i < 4; i++) {
        int newX = current->x + dx[i];
        int newY = current->y + dy[i];

        // Bounds Check (Ensure node exists in graph)
        if (newX >= 0 && newX < COLS && newY >= 0 && newY < ROWS) {
            Node *neighbor = &grid[newY][newX];

            // Graph Logic: If not a wall and we found a shorter path
            if (!neighbor->isWall && !neighbor->visited) {
                int newDist = current->distance + 1; // Edge weight is 1

                if (newDist < neighbor->distance) {
                    neighbor->distance = newDist;
                    neighbor->parent = current;
                    pq.push({newDist, neighbor});
                }
            }
        }
    }
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dijkstra Visualizer - C++ & Raylib");
    SetTargetFPS(60); // Control speed of animation

    InitGrid();

    while (!WindowShouldClose()) {
        // --- INPUT HANDLING ---

        // Left Click to draw Walls (Remove Edges)
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !algorithmRunning) {
            Vector2 mouse = GetMousePosition();
            int gridX = mouse.x / CELL_WIDTH;
            int gridY = mouse.y / CELL_HEIGHT;

            if (gridX >= 0 && gridX < COLS && gridY >= 0 && gridY < ROWS) {
                // Don't draw walls on start or end
                if (&grid[gridY][gridX] != startNode && &grid[gridY][gridX] != endNode)
                    grid[gridY][gridX].isWall = true;
            }
        }

        // Right Click to erase Walls
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && !algorithmRunning) {
            Vector2 mouse = GetMousePosition();
            int gridX = mouse.x / CELL_WIDTH;
            int gridY = mouse.y / CELL_HEIGHT;
            if (gridX >= 0 && gridX < COLS && gridY >= 0 && gridY < ROWS)
                grid[gridY][gridX].isWall = false;
        }

        // Press SPACE to Start
        if (IsKeyPressed(KEY_SPACE) && !algorithmRunning) {
            algorithmRunning = true;
        }

        // Press R to Reset
        if (IsKeyPressed(KEY_R)) {
            InitGrid();
        }

        // --- UPDATE LOGIC ---
        if (algorithmRunning) {
            // Process a few nodes per frame to speed it up
            // Increase this number to make it faster
            for (int i = 0; i < 5; i++)
                UpdateDijkstra();
        }

        // --- DRAWING ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int y = 0; y < ROWS; y++) {
            for (int x = 0; x < COLS; x++) {
                Node *n = &grid[y][x];

                // Color Logic
                if (n->isWall)
                    n->Draw(BLACK); // Obstacle
                else if (n == startNode)
                    n->Draw(GREEN); // Start
                else if (n == endNode)
                    n->Draw(RED); // End
                else if (n->visited)
                    n->Draw(BLUE); // Visited (Explored)
                else
                    n->Draw(LIGHTGRAY); // Unvisited

                // Draw Grid Lines
                DrawRectangleLines(x * CELL_WIDTH, y * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, GRAY);
            }
        }

        // Draw Final Path
        // We backtrack from EndNode -> Parent -> Parent... until StartNode
        if (pathFound) {
            Node *curr = endNode->parent;
            while (curr != nullptr && curr != startNode) {
                curr->Draw(YELLOW);
                curr = curr->parent;
            }
        }

        DrawFPS(10, 10);
        if (pathFound) {
            DrawText(TextFormat("Path length: %d", pathLengthDisplay), 10, 35, 20, DARKGREEN);
            DrawText(TextFormat("Visited: %d", visitedCount), 10, 60, 20, DARKBLUE);
        }
        if (!algorithmRunning)
            DrawText("Draw Walls with Mouse. SPACE to Start. R to Reset", 10, SCREEN_HEIGHT - 30, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}