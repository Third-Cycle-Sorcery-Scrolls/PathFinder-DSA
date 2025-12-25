#pragma once
#include "PathAlgorithm.h"
#include "BFS.h"
#include "core/AlgorithmType.h"
#include "DFS.h"
#include <memory>//for std::unique_ptr which manages dynamic memory automatically
//inline function to create algorithm instances based on AlgorithmType
inline std::unique_ptr<PathAlgorithm> createAlgorithm(AlgorithmType type) {
    switch (type) {
        case AlgorithmType::BFS:
            return std::make_unique<BFS>();
        // Future algorithms can be added here
        //case AlgorithmType::DIJKSTRA:
        //    return std::make_unique<Dijkstra>();
        //case AlgorithmType::ASTAR:
        //    return std::make_unique<AStar>();
        case AlgorithmType::DFS:
           return std::make_unique<DFS>();
        default:
            return nullptr;
    }
}