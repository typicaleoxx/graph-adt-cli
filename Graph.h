#ifndef GRAPH_H
#define GRAPH_H

// Graph.h - manages graph structure with vertex and edge objects plus adjacency relationships

#include <vector>
#include <string>
#include <map>

using namespace std;

class Vertex;
class Edge;

class Graph {
private:
    vector<Vertex*> vertexList;
    vector<Edge*> edgeList;
    map<string, Vertex*> vertexMap;
    map<Vertex*, vector<pair<Vertex*, double>>> adjacencyList;

public:
    // constructor that reads file and builds complete graph structure with objects
    Graph(string filename);
    
    // destructor that frees all allocated memory
    ~Graph();
    
    // return collection of all vertex objects in the graph
    vector<Vertex*> vertices();
    
    // return collection of all edge objects in the graph
    vector<Edge*> edges();
    
    // build adjacency list connections from all edges
    void buildAdjacencyList();
};

#endif
