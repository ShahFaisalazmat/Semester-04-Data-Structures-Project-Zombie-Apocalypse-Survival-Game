#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>

// Graph class to represent the city map
class Graph {
private:
    int numVertices;                           // Number of vertices (cells)
    std::vector<std::list<int>> adjacencyList; // Adjacency list representation
    std::vector<char> nodeTypes;               // Type of each node: 'W' (Wall), 'I' (Item), 'Z' (Zombie), etc.

public:
    // Constructor
    Graph(int vertices);

    // Add an edge between two nodes (bidirectional)
    void addEdge(int v, int w);

    // Remove an edge between two nodes (bidirectional)
    void removeEdge(int v, int w);

    // Check if there's an edge between two nodes
    bool hasEdge(int v, int w) const;

    // Get all adjacent nodes
    std::list<int> getAdjacent(int v) const;

    // Set node type (wall, item, etc.)
    void setNodeType(int v, char type);

    // Get node type
    char getNodeType(int v) const;

    // Get number of vertices
    int getNumVertices() const;
};

#endif // GRAPH_H#pragma once
