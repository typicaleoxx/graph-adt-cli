#include "Vertex.h"
#include "Edge.h"
#include <algorithm>

// initialize a vertex by storing its location name
Vertex::Vertex(string val) : value(val) {
}

// return the name of this vertex (operator*)
string Vertex::operator*() const {
    return value;
}

// return the name of this vertex
string Vertex::getValue() const {
    return value;
}

// attach an edge to this vertex so we track all connected edges
void Vertex::addIncidentEdge(Edge* e) {
    incidentEdgeList.push_back(e);
}

// return the collection of all edges connected to this vertex
vector<Edge*> Vertex::getIncidentEdges() const {
    return incidentEdgeList;
}

// return the collection of all edges connected to this vertex (spec name)
vector<Edge*> Vertex::incidentEdges() const {
    return incidentEdgeList;
}

// remove an edge from this vertex's incident edge list
void Vertex::removeIncidentEdge(Edge* e) {
    incidentEdgeList.erase(remove(incidentEdgeList.begin(), incidentEdgeList.end(), e), incidentEdgeList.end());
}

// check if another vertex is a neighbor by looking through incident edges
bool Vertex::isAdjacentTo(Vertex* v) const {
    if (v == nullptr) return false;
    for (Edge* e : incidentEdgeList) {
        if (e->opposite(this) == v) {
            return true;
        }
    }
    return false;
}
