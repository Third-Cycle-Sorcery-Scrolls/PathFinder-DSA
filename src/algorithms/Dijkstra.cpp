#include "Dijkstra.h"
#include <queue>
#include <vector>
#include <limits>

struct DijkstraNode {
    int node;
    float dist;

    bool operator>(const DijkstraNode& other) const {
        return dist > other.dist;
    }
};

PathResult Dijkstra::run(const Graph& graph, int start, int end) {
    PathResult result;
    int n = graph.nodes.size();

    std::vector<bool> visited(n, false);
    std::vector<int> parent(n, -1);
    std::vector<float> dist(n, std::numeric_limits<float>::infinity());

    std::priority_queue<
        DijkstraNode,
        std::vector<DijkstraNode>,
        std::greater<DijkstraNode>
    > pq;

    dist[start] = 0.0f;
    pq.push({ start, 0.0f });

    while (!pq.empty()) {
        int u = pq.top().node;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        result.visitedOrder.push_back(u);

        if (u == end) break;

        for (const auto& edge : graph.adjList[u]) {
            int v = edge.to;
            float newDist = dist[u] + edge.weight;

            if (newDist < dist[v]) {
                dist[v] = newDist;
                parent[v] = u;
                pq.push({ v, dist[v] });
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
