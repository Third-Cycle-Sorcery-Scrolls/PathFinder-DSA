// #include "../raylib/include/raylib.h"
#include "C:\Users\aaman\OneDrive\Desktop\SWEY3 Sem1\DSA\Route Finder\raylib\include\raylib.h"
#include "core/Constants.h"
#include "core/Application.h"

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "PathFinder DSA - BFS Demo");
    SetTargetFPS(60);

    Application app;
    app.init();

    float stepTimer = 0.0f;
    const float STEP_DELAY = 0.15f; // seconds per algorithm step (adjust)

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        stepTimer += deltaTime;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Only advance algorithm when enough time has passed
        if (stepTimer >= STEP_DELAY) {
            app.update();      // ONE algorithm step
            stepTimer = 0.0f;
        }

        app.render();
        DrawFPS(10, 10);
        if (IsKeyPressed(KEY_R)) {
            app.init();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
