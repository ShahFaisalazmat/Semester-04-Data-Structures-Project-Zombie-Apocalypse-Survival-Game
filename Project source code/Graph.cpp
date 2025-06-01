#include "C:\Users\Shah Faisal\source\repos\Data Structures Project\Data Structures Project\Graph.h"
#include <algorithm>

// Constructor
Graph::Graph(int vertices) {
    numVertices = vertices;
    adjacencyList.resize(vertices);
    nodeTypes.resize(vertices, ' '); // Initialize all nodes as empty
}

// Add an edge between two nodes (bidirectional)
void Graph::addEdge(int v, int w) {
    // Ensure nodes are valid
    if (v < 0 || v >= numVertices || w < 0 || w >= numVertices) {
        return;
    }

    // Add edges in both directions (undirected graph)
    adjacencyList[v].push_back(w);
    adjacencyList[w].push_back(v);
}

// Remove an edge between two nodes (bidirectional)
void Graph::removeEdge(int v, int w) {
    // Ensure nodes are valid
    if (v < 0 || v >= numVertices || w < 0 || w >= numVertices) {
        return;
    }

    // Remove edges in both directions
    adjacencyList[v].remove(w);
    adjacencyList[w].remove(v);
}

// Check if there's an edge between two nodes
bool Graph::hasEdge(int v, int w) const {
    // Ensure nodes are valid
    if (v < 0 || v >= numVertices || w < 0 || w >= numVertices) {
        return false;
    }

    // Check if w is in the adjacency list of v
    auto& adjList = adjacencyList[v];
    return std::find(adjList.begin(), adjList.end(), w) != adjList.end();
}

// Get all adjacent nodes
std::list<int> Graph::getAdjacent(int v) const {
    // Ensure node is valid
    if (v < 0 || v >= numVertices) {
        return std::list<int>();
    }

    return adjacencyList[v];
}

// Set node type (wall, item, etc.)
void Graph::setNodeType(int v, char type) {
    // Ensure node is valid
    if (v < 0 || v >= numVertices) {
        return;
    }

    nodeTypes[v] = type;
}

// Get node type
char Graph::getNodeType(int v) const {
    // Ensure node is valid
    if (v < 0 || v >= numVertices) {
        return ' ';
    }

    return nodeTypes[v];
}

// Get number of vertices
int Graph::getNumVertices() const {
    return numVertices;
}