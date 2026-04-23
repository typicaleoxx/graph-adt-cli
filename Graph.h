#ifndef GRAPH_H
#define GRAPH_H

// Graph.h - contains graph class for parsing input file and storing raw vertex and edge data

#include <vector>
#include <string>

using namespace std;

class Graph {
private:
    vector<string> vertexList;
    vector<tuple<string, string, double>> edgeList;

public:
    // constructor that opens file and extracts raw vertex and edge information
    Graph(string filename);
    
    // return list of all vertex names
    vector<string> getVertices();
    
    // return list of all edges as (vertex1, vertex2, weight) tuples
    vector<tuple<string, string, double>> getEdges();
};

#endif
