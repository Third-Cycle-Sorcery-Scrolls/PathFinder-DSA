#include "../src/algorithms/DFS.h"
#include "../src/graph/Graph.h"
#include <cassert>


void test_dfs_simple_path() {
    Graph g;

    for (int i = 0; i < 4; i++)
        g.addNode(Node{});

    g.addEdge(0, 1, 1.0);
    g.addEdge(1, 2, 1.0);
    g.addEdge(2, 3, 1.0);

    PathResult res = DFS::findPath(g, 0, 3);

    assert(!res.path.empty());
    assert(res.path.front() == 0);
    assert(res.path.back() == 3);
}

void test_dfs_unreachable() {
    Graph g;

    for (int i = 0; i < 3; i++)
        g.addNode(Node{});

    g.addEdge(0, 1, 1.0);

    PathResult res = DFS::findPath(g, 0, 2);

    assert(res.path.empty());
}

int main() {
    test_dfs_simple_path();
    test_dfs_unreachable();
    return 0;
}

