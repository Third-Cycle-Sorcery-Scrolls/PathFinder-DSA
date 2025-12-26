#include "DFS.h"
#include <stack>
#include <vector>
#include <algorithm>

PathResult DFS::run(const Graph& graph, int start, int end) {
    int goal = end;
    PathResult result;

    int n = graph.nodes.size();
    std::vector<bool> visited(n, false);
    std::vector<int> parent(n, -1);

    struct DFSState {
        int node;
        bool returning;
    };

    std::stack<DFSState> st;
    st.push({start, false});
    visited[start] = true;

    while (!st.empty()) {
        DFSState state = st.top();
        st.pop();

        int current = state.node;

        if (state.returning) {
            // Backtracking event
            result.visitedOrder.push_back(current);
            continue;
        }

        // Forward visit
        result.visitedOrder.push_back(current);

        if (current == goal)
            break;

        // Mark backtracking step
        st.push({current, true});

        // Push neighbors in reverse order (important for DFS correctness)
        for (auto it = graph.adjList[current].rbegin();
             it != graph.adjList[current].rend(); ++it) {

            int neighbor = it->to;

            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;
                st.push({neighbor, false});
            }
        }
    }

    // Reconstruct path
    if (visited[goal]) {
        for (int v = goal; v != -1; v = parent[v]) {
            result.path.push_back(v);
        }
        std::reverse(result.path.begin(), result.path.end());
    }

    result.totalCost = 0.0f; // DFS ignores weights
    return result;
}


