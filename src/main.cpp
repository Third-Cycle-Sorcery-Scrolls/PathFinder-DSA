#include "../raylib/include/raylib.h"
// #include "C:\Users\aaman\OneDrive\Desktop\SWEY3 Sem1\DSA\Route Finder\raylib\include\raylib.h"
#include "core/Constants.h"
#include "core/Application.h"

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "PathFinder DSA - BFS Demo");
    SetTargetFPS(2);// Set desired framerate
    Application app;
    app.init();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        app.update();
        app.render();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
