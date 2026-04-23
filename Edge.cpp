#include "Edge.h"
#include "Vertex.h"

// Edge.cpp - implements the edge class methods for storing and accessing connection data

// initialize an edge with two endpoints and a distance weight
Edge::Edge(Vertex* v1, Vertex* v2, double w) : endpoint1(v1), endpoint2(v2), label(w) {
}

// return both endpoints of this edge as a pair
pair<Vertex*, Vertex*> Edge::getEndVertices() {
    return make_pair(endpoint1, endpoint2);
}

// given one endpoint, return the other endpoint of this edge
Vertex* Edge::getOtherEndpoint(Vertex* v) {
    if (v == endpoint1) {
        return endpoint2;
    } else if (v == endpoint2) {
        return endpoint1;
    }
    return nullptr;
}

// return the distance weight of this edge
double Edge::getLabel() {
    return label;
}
