#include <vector>
#include <string>
#include <map>
#include <algorithm>
// #include <tre

using namespace std;
// Node/Location Class
class Location {
private:
    int id;
    string name;
    double x, y; // Coordinates for visualization
public:
    // Constructor, getters, setters
};

// Edge/Road Class
class Road {
private:
    int source, destination;
    double distance; // Weight
    string roadType; // Highway, Local, etc.
    bool isActive;
public:
    // Constructor, getters, setters
};

// Graph Class
class MapGraph {
private:
    vector<Location> vertices;
    vector<vector<pair<int, double>>> adjacencyList; // adjList[source] = {dest, weight}
    unordered_map<int, unordered_map<int, Road>> edgeDetails;
    
public:
    // Graph operations
    void addLocation(Location loc);
    void removeLocation(int locId);
    void addRoad(int src, int dest, double weight, string type);
    void removeRoad(int src, int dest);
    void updateRoad(int src, int dest, double newWeight);
    
    // Path finding
    vector<vector<int>> findAllPaths(int src, int dest, int maxPaths = 3);
    vector<int> findShortestPath(int src, int dest);
    
    // Visualization helper
    void printPath(vector<int> path);
};