#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Graph.cpp - implements graph construction by creating vertex and edge objects and building adjacency relationships

// parse input file and create vertex and edge objects then build adjacency list
Graph::Graph(string filename) {
    ifstream inputFile(filename);
    
    // check if file opened successfully
    if (!inputFile.is_open()) {
        cerr << "error: unable to open file " << filename << endl;
        return;
    }
    
    // read first line and create vertex objects for each location
    string firstLine;
    getline(inputFile, firstLine);
    stringstream vertexStream(firstLine);
    string vertexName;
    
    while (vertexStream >> vertexName) {
        // create new vertex object and store it in both list and map
        Vertex* newVertex = new Vertex(vertexName);
        vertexList.push_back(newVertex);
        vertexMap[vertexName] = newVertex;
    }
    
    // read remaining lines and create edge objects with weights
    string edgeLine;
    while (getline(inputFile, edgeLine)) {
        if (edgeLine.empty()) continue;
        
        stringstream edgeStream(edgeLine);
        string v1Name, v2Name;
        double weight;
        
        // parse vertex names and weight from the line
        edgeStream >> v1Name >> v2Name >> weight;
        
        // find vertices and create edge object connecting them
        if (vertexMap.find(v1Name) != vertexMap.end() && vertexMap.find(v2Name) != vertexMap.end()) {
            Vertex* v1 = vertexMap[v1Name];
            Vertex* v2 = vertexMap[v2Name];
            Edge* newEdge = new Edge(v1, v2, weight);
            edgeList.push_back(newEdge);
            
            // add edge to both vertices incident edge lists
            v1->addIncidentEdge(newEdge);
            v2->addIncidentEdge(newEdge);
        }
    }
    
    // build adjacency list from all edges
    buildAdjacencyList();
    inputFile.close();
}

// clean up all dynamically allocated vertex and edge objects
Graph::~Graph() {
    for (Edge* edge : edgeList) {
        delete edge;
    }
    for (Vertex* vertex : vertexList) {
        delete vertex;
    }
}

// return vector of all vertex objects in the graph
vector<Vertex*> Graph::vertices() {
    return vertexList;
}

// return vector of all edge objects in the graph
vector<Edge*> Graph::edges() {
    return edgeList;
}

// build adjacency list mapping each vertex to its neighbors with weights
void Graph::buildAdjacencyList() {
    for (Edge* edge : edgeList) {
        // get both endpoints of the edge
        pair<Vertex*, Vertex*> endpoints = edge->getEndVertices();
        Vertex* v1 = endpoints.first;
        Vertex* v2 = endpoints.second;
        double weight = edge->getLabel();
        
        // add both directions since graph is undirected
        adjacencyList[v1].push_back(make_pair(v2, weight));
        adjacencyList[v2].push_back(make_pair(v1, weight));
    }
}
