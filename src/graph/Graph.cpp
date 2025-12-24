#include "Graph.h"

/*
addNode: Adds a new node to the graph
param node: The node to be added

*/
void Graph::addNode(const Node& node) {
    nodes.push_back(node);
    adjList.push_back({});// Initialize adjacency list for the new node
}
/*
addEdge: Adds a new edge to the graph
param from: Identifier of the source node
param to: Identifier of the destination node
param weight: Weight of the edge
param bidirectional: If true, adds an edge in both directions (default is true)
*/
void Graph::addEdge(int from, int to, double weight, bool bidirectional) {
    adjList[from].push_back({to, weight});
    if (bidirectional) {
        adjList[to].push_back({from, weight});
    }
}