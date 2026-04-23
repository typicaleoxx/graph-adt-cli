#ifndef EDGE_H
#define EDGE_H

// Edge.h - defines the edge class representing a weighted connection between two vertices

#include <string>

using namespace std;

class Vertex;

class Edge {
private:
    Vertex* endpoint1;
    Vertex* endpoint2;
    double label;

public:
    // create an edge connecting two vertices with a weight value
    Edge(Vertex* v1, Vertex* v2, double w);
    
    // return the two vertices at the ends of this edge
    pair<Vertex*, Vertex*> getEndVertices();
    
    // return the other endpoint when given one endpoint
    Vertex* getOtherEndpoint(Vertex* v);
    
    // return the weight of this edge
    double getLabel();
};

#endif
