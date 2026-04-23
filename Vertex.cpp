#include "Vertex.h"
#include "Edge.h"

// Vertex.cpp - implements the vertex class methods for managing node data and connections

// initialize a vertex by storing its location name
Vertex::Vertex(string val) : value(val) {
}

// return the name of this vertex
string Vertex::getValue() {
    return value;
}

// attach an edge to this vertex so we track all connected edges
void Vertex::addIncidentEdge(Edge* e) {
    incidentEdgeList.push_back(e);
}

// return the collection of all edges connected to this vertex
vector<Edge*> Vertex::getIncidentEdges() {
    return incidentEdgeList;
}

// check if another vertex is a neighbor by looking through incident edges
bool Vertex::isAdjacentTo(Vertex* v) {
    for (Edge* e : incidentEdgeList) {
        if (e->getOtherEndpoint(this) == v) {
            return true;
        }
    }
    return false;
}
