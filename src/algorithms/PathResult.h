#pragma once
#include <vector>

/*
 UI Contract for the result of a pathfinding algorithm
 path: Sequence of node identifiers representing the found path
 visitedOrder: Sequence of node identifiers in the order they were visited
 totalCost: Total cost associated with the found path
*/

struct PathResult
{
    std::vector<int> path;
    std::vector<int> visitedOrder;
    float totalCost = 0.0f;
};
