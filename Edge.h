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
    
    // return the weight label of this edge (operator*)
    double operator*() const;
    
    // return the two vertices at the ends of this edge
    pair<Vertex*, Vertex*> endVertices() const;
    
    // return the other endpoint when given one endpoint
    Vertex* opposite(const Vertex* v) const;
    
    // check if this edge is adjacent to another edge
    bool isAdjacentTo(Edge* e) const;
    
    // check if this edge is incident on a given vertex
    bool isIncidentOn(Vertex* v) const;
};

#endif
