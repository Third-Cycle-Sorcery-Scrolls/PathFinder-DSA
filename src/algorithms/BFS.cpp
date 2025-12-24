#include "BFS.h"
#include <queue>
#include <vector>

PathResult BFS::run(const Graph& graph, int start, int end) {
    PathResult result;
    int n = graph.nodes.size();
    std::vector<bool> visited(n, false);
    std::vector<int> parent(n, -1);
    std::queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        result.visitedOrder.push_back(u);

        if (u == end) break;

        for (const auto& edge : graph.adjList[u]) {
            int v = edge.to;
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    // Reconstruct path
    int cur = end;
    while (cur != -1) {
        result.path.insert(result.path.begin(), cur);
        cur = parent[cur];
    }

    if (result.path.front() != start) result.path.clear();

    return result;
}
