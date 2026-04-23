#include "Edge.h"
#include "Vertex.h"

// initialize an edge with two endpoints and a distance weight
Edge::Edge(Vertex* v1, Vertex* v2, double w) : endpoint1(v1), endpoint2(v2), label(w) {
}

// return the weight label of this edge (operator*)
double Edge::operator*() const {
    return label;
}

// return both endpoints of this edge as a pair
pair<Vertex*, Vertex*> Edge::endVertices() const {
    return make_pair(endpoint1, endpoint2);
}

// given one endpoint, return the other endpoint of this edge
Vertex* Edge::opposite(const Vertex* v) const {
    if (v == endpoint1) {
        return endpoint2;
    } else if (v == endpoint2) {
        return endpoint1;
    }
    return nullptr;
}

// check if this edge is adjacent to another edge (shares a common vertex)
bool Edge::isAdjacentTo(Edge* e) const {
    if (e == nullptr) return false;
    pair<Vertex*, Vertex*> otherEndpoints = e->endVertices();
    return (endpoint1 == otherEndpoints.first || endpoint1 == otherEndpoints.second ||
            endpoint2 == otherEndpoints.first || endpoint2 == otherEndpoints.second);
}

// check if this edge is incident on a given vertex
bool Edge::isIncidentOn(Vertex* v) const {
    return (endpoint1 == v || endpoint2 == v);
}
