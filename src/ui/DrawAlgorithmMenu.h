#pragma once
#include "core/AlgorithmInfo.h"
#include "raylib.h"
#include <vector>

void DrawAlgorithmMenu(
    const std::vector<AlgorithmInfo>& algorithms,
    int selectedIndex
) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int padding = 40;
    int itemSpacing = 360;
    int y = screenHeight - 40;

    for (size_t i = 0; i < algorithms.size(); i++) {
        int x = padding + i * itemSpacing;

        Color color = (i == selectedIndex) ? ORANGE : DARKGRAY;

        DrawText(
            TextFormat("%zu - %s", i + 1, algorithms[i].name),
            x, y,
            20,
            color
        );
    }
}
