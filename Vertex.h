#ifndef VERTEX_H
#define VERTEX_H

// Vertex.h - defines the vertex class representing a single node or location in the graph

#include <string>
#include <vector>

using namespace std;

class Edge;

class Vertex {
private:
    string value;
    vector<Edge*> incidentEdgeList;

public:
    // create a vertex with a given location name
    Vertex(string val);
    
    // return the name of this vertex (operator*)
    string operator*() const;
    
    // return the name of this vertex
    string getValue() const;
    
    // add an edge connected to this vertex
    void addIncidentEdge(Edge* e);
    
    // return all edges connected to this vertex
    vector<Edge*> getIncidentEdges() const;
    
    // return all edges connected to this vertex
    vector<Edge*> incidentEdges() const;
    
    // remove an edge from this vertex's incident edge list
    void removeIncidentEdge(Edge* e);
    
    // check if another vertex is directly connected to this one
    bool isAdjacentTo(Vertex* v) const;
};

#endif
