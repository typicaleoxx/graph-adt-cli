#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

// Graph.cpp - implements graph construction, modification operations like insert and erase for vertices and edges

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

// check if a vertex exists and add it if not already present
void Graph::insertVertex(string x) {
    // verify vertex does not already exist in the graph
    if (vertexMap.find(x) == vertexMap.end()) {
        // create new vertex and add to lists
        Vertex* newVertex = new Vertex(x);
        vertexList.push_back(newVertex);
        vertexMap[x] = newVertex;
    }
}

// add a new edge between two existing vertices with a distance weight
void Graph::insertEdge(string v, string w, double x) {
    // validate both vertices exist in the graph
    if (vertexMap.find(v) == vertexMap.end() || vertexMap.find(w) == vertexMap.end()) {
        cerr << "error: vertex not found" << endl;
        return;
    }
    
    // check if edge already exists between these vertices
    Vertex* v1 = vertexMap[v];
    Vertex* v2 = vertexMap[w];
    if (findEdge(v1, v2) != nullptr) {
        cerr << "error: edge already exists" << endl;
        return;
    }
    
    // create new edge and add it to graph
    Edge* newEdge = new Edge(v1, v2, x);
    edgeList.push_back(newEdge);
    v1->addIncidentEdge(newEdge);
    v2->addIncidentEdge(newEdge);
    
    // update adjacency list with new edge in both directions
    adjacencyList[v1].push_back(make_pair(v2, x));
    adjacencyList[v2].push_back(make_pair(v1, x));
}

// remove a vertex and all edges connected to it from the graph
void Graph::eraseVertex(string v) {
    // check if vertex exists
    if (vertexMap.find(v) == vertexMap.end()) {
        cerr << "error: vertex not found" << endl;
        return;
    }
    
    Vertex* vertex = vertexMap[v];
    
    // get all incident edges before removing
    vector<Edge*> incidentEdges = vertex->getIncidentEdges();
    
    // remove all edges connected to this vertex
    for (Edge* edge : incidentEdges) {
        pair<Vertex*, Vertex*> endpoints = edge->getEndVertices();
        Vertex* other = (endpoints.first == vertex) ? endpoints.second : endpoints.first;
        
        // remove edge from adjacency list
        auto& adjList = adjacencyList[other];
        adjList.erase(remove_if(adjList.begin(), adjList.end(),
            [vertex](const pair<Vertex*, double>& p) { return p.first == vertex; }),
            adjList.end());
        
        // remove edge from edge list
        edgeList.erase(remove(edgeList.begin(), edgeList.end(), edge), edgeList.end());
        delete edge;
    }
    
    // remove vertex from adjacency list
    adjacencyList.erase(vertex);
    
    // remove vertex from lists
    vertexList.erase(remove(vertexList.begin(), vertexList.end(), vertex), vertexList.end());
    vertexMap.erase(v);
    delete vertex;
}

// remove an edge between two vertices from the graph
void Graph::eraseEdge(string v, string w) {
    // validate both vertices exist
    if (vertexMap.find(v) == vertexMap.end() || vertexMap.find(w) == vertexMap.end()) {
        cerr << "error: vertex not found" << endl;
        return;
    }
    
    Vertex* v1 = vertexMap[v];
    Vertex* v2 = vertexMap[w];
    
    // find the edge between the two vertices
    Edge* edgeToRemove = findEdge(v1, v2);
    if (edgeToRemove == nullptr) {
        cerr << "error: edge not found" << endl;
        return;
    }
    
    // remove edge from both vertices incident lists
    vector<Edge*>& v1Edges = const_cast<vector<Edge*>&>(v1->getIncidentEdges());
    v1Edges.erase(remove(v1Edges.begin(), v1Edges.end(), edgeToRemove), v1Edges.end());
    
    vector<Edge*>& v2Edges = const_cast<vector<Edge*>&>(v2->getIncidentEdges());
    v2Edges.erase(remove(v2Edges.begin(), v2Edges.end(), edgeToRemove), v2Edges.end());
    
    // remove edge from adjacency list
    auto& adj1 = adjacencyList[v1];
    adj1.erase(remove_if(adj1.begin(), adj1.end(),
        [v2](const pair<Vertex*, double>& p) { return p.first == v2; }),
        adj1.end());
    
    auto& adj2 = adjacencyList[v2];
    adj2.erase(remove_if(adj2.begin(), adj2.end(),
        [v1](const pair<Vertex*, double>& p) { return p.first == v1; }),
        adj2.end());
    
    // remove edge from edge list and delete
    edgeList.erase(remove(edgeList.begin(), edgeList.end(), edgeToRemove), edgeList.end());
    delete edgeToRemove;
}

// search for an edge between two vertices and return it if found
Edge* Graph::findEdge(Vertex* v1, Vertex* v2) {
    for (Edge* edge : edgeList) {
        pair<Vertex*, Vertex*> endpoints = edge->getEndVertices();
        if ((endpoints.first == v1 && endpoints.second == v2) ||
            (endpoints.first == v2 && endpoints.second == v1)) {
            return edge;
        }
    }
    return nullptr;
}
