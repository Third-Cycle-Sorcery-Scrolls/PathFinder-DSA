#include "AStar.h"
#include <queue>
#include <vector>
#include <limits>
#include <cmath>

struct AStarNode {
    int node;
    float fScore;

    bool operator>(const AStarNode& other) const {
        return fScore > other.fScore;
    }
};


float AStar::heuristic(const Graph& graph, int a, int b) {
    auto& p1 = graph.nodes[a].position;
    auto& p2 = graph.nodes[b].position;
    return std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y); // Manhattan
}


PathResult AStar::run(const Graph& graph, int start, int end) {
    
    PathResult result;
    int n = graph.nodes.size();

    std::vector<bool> visited(n, false);
    std::vector<int> parent(n, -1);

    std::vector<float> gScore(n, std::numeric_limits<float>::infinity());
    std::vector<float> fScore(n, std::numeric_limits<float>::infinity());

    std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> openSet;

    gScore[start] = 0.0f;
    fScore[start] = heuristic(graph, start, end);

    openSet.push({ start, fScore[start] });

    while (!openSet.empty()) {
        int u = openSet.top().node;
        openSet.pop();

        if (visited[u]) continue;
        visited[u] = true;

        result.visitedOrder.push_back(u);

        if (u == end) break;

        for (const auto& edge : graph.adjList[u]) {
            int v = edge.to;
            float tentativeG = gScore[u] + edge.weight;

            if (tentativeG < gScore[v]) {
                parent[v] = u;
                gScore[v] = tentativeG;
                fScore[v] = tentativeG + heuristic(graph, v, end);
                openSet.push({ v, fScore[v] });
            }
        }
    }

    // Reconstruct path
    int cur = end;
    while (cur != -1) {
        result.path.insert(result.path.begin(), cur);
        cur = parent[cur];
    }

    if (result.path.empty() || result.path.front() != start)
        result.path.clear();

    return result;
}
