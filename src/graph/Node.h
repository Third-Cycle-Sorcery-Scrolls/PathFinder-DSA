#pragma once
#include "raylib.h"
#include <string>
/*
 id: Unique identifier for the node
 position: 2D position of the node in the graph, provided by raylib's Vector2 structure
*/

struct Node
{
    int id;
    Vector2 position;
    std::string label;
    
};


