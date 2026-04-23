#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>

// Graph.cpp - implements graph construction, modification operations like insert and erase for vertices and edges

// parse input file and create vertex and edge objects then build adjacency list
Graph::Graph(string filename) {
    // validate filename is not empty
    if (filename.empty()) {
        cerr << "error: filename cannot be empty" << endl;
        return;
    }
    
    ifstream inputFile(filename);
    
    // check if file opened successfully
    if (!inputFile.is_open()) {
        cerr << "error: unable to open file " << filename << endl;
        return;
    }
    
    // read first line and create vertex objects for each location
    string firstLine;
    if (!getline(inputFile, firstLine)) {
        cerr << "error: file is empty or cannot be read" << endl;
        inputFile.close();
        return;
    }
    
    stringstream vertexStream(firstLine);
    string vertexName;
    int vertexCount = 0;
    
    while (vertexStream >> vertexName) {
        // validate vertex name is not empty
        if (vertexName.empty()) {
            cerr << "error: empty vertex name found" << endl;
            continue;
        }
        
        // check for duplicate vertices
        if (vertexMap.find(vertexName) != vertexMap.end()) {
            cerr << "error: duplicate vertex name " << vertexName << endl;
            continue;
        }
        
        // create new vertex object and store it in both list and map
        Vertex* newVertex = new Vertex(vertexName);
        vertexList.push_back(newVertex);
        vertexMap[vertexName] = newVertex;
        vertexCount++;
    }
    
    // validate at least one vertex was read
    if (vertexCount == 0) {
        cerr << "error: no vertices found in file" << endl;
        inputFile.close();
        return;
    }
    
    // read remaining lines and create edge objects with weights
    string edgeLine;
    int lineNumber = 1;
    while (getline(inputFile, edgeLine)) {
        lineNumber++;
        if (edgeLine.empty()) continue;
        
        stringstream edgeStream(edgeLine);
        string v1Name, v2Name;
        double weight;
        
        // parse vertex names and weight from the line
        if (!(edgeStream >> v1Name >> v2Name >> weight)) {
            cerr << "error: invalid edge format at line " << lineNumber << endl;
            continue;
        }
        
        // validate edge weight is positive
        if (weight < 0) {
            cerr << "error: negative weight not allowed at line " << lineNumber << endl;
            continue;
        }
        
        // find vertices and create edge object connecting them
        if (vertexMap.find(v1Name) == vertexMap.end() || vertexMap.find(v2Name) == vertexMap.end()) {
            cerr << "error: vertex not found in edge definition at line " << lineNumber << endl;
            continue;
        }
        
        // find vertices and create edge object connecting them
        if (vertexMap.find(v1Name) == vertexMap.end() || vertexMap.find(v2Name) == vertexMap.end()) {
            cerr << "error: vertex not found in edge definition at line " << lineNumber << endl;
            continue;
        }
        
        Vertex* v1 = vertexMap[v1Name];
        Vertex* v2 = vertexMap[v2Name];
        
        // check for duplicate edge
        if (findEdge(v1, v2) != nullptr) {
            cerr << "error: duplicate edge between " << v1Name << " and " << v2Name << endl;
            continue;
        }
        
        // create and add new edge
        Edge* newEdge = new Edge(v1, v2, weight);
        edgeList.push_back(newEdge);
        
        // add edge to both vertices incident edge lists
        v1->addIncidentEdge(newEdge);
        v2->addIncidentEdge(newEdge);
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
        pair<Vertex*, Vertex*> endpoints = edge->endVertices();
        Vertex* v1 = endpoints.first;
        Vertex* v2 = endpoints.second;
        double weight = **edge;
        
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
    
    cout << "Edge inserted" << endl;
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
    vector<Edge*> incidentEdges = vertex->incidentEdges();
    
    // remove all edges connected to this vertex
    for (Edge* edge : incidentEdges) {
        pair<Vertex*, Vertex*> endpoints = edge->endVertices();
        Vertex* other = (endpoints.first == vertex) ? endpoints.second : endpoints.first;
        
        // remove edge from adjacency list
        auto& adjList = adjacencyList[other];
        adjList.erase(remove_if(adjList.begin(), adjList.end(),
            [vertex](const pair<Vertex*, double>& p) { return p.first == vertex; }),
            adjList.end());

        // remove edge from the other vertex's incident edge list before deleting
        other->removeIncidentEdge(edge);

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
    
    cout << "Vertex removed" << endl;
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
    
    // remove edge from both vertices incident lists using the remove method
    v1->removeIncidentEdge(edgeToRemove);
    v2->removeIncidentEdge(edgeToRemove);
    
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
        pair<Vertex*, Vertex*> endpoints = edge->endVertices();
        if ((endpoints.first == v1 && endpoints.second == v2) ||
            (endpoints.first == v2 && endpoints.second == v1)) {
            return edge;
        }
    }
    return nullptr;
}

// find all edges connected to a specific vertex
vector<Edge*> Graph::incidentEdges(string v) {
    vector<Edge*> result;
    
    if (vertexMap.find(v) == vertexMap.end()) {
        return result;
    }

    // return all edges from the vertex's incident edge list
    Vertex* vertex = vertexMap[v];
    return vertex->incidentEdges();
}

// check if two vertices are neighbors by looking in adjacency list
bool Graph::isAdjacentTo(string v, string w) {
    // validate both vertices exist
    if (vertexMap.find(v) == vertexMap.end() || vertexMap.find(w) == vertexMap.end()) {
        cerr << "error: vertex not found" << endl;
        return false;
    }
    
    Vertex* vertex1 = vertexMap[v];
    Vertex* vertex2 = vertexMap[w];
    
    // check if vertex2 appears in vertex1's adjacency list
    if (adjacencyList.find(vertex1) != adjacencyList.end()) {
        for (auto& neighbor : adjacencyList[vertex1]) {
            if (neighbor.first == vertex2) {
                return true;
            }
        }
    }
    
    return false;
}

// find a path between two vertices using breadth first search algorithm
vector<string> Graph::findPath(string start, string end) {
    vector<string> path;
    
    // validate both vertices exist
    if (vertexMap.find(start) == vertexMap.end() || vertexMap.find(end) == vertexMap.end()) {
        cerr << "error: vertex not found" << endl;
        return path;
    }
    
    Vertex* startVertex = vertexMap[start];
    Vertex* endVertex = vertexMap[end];
    
    // bfs to find shortest path between vertices
    set<Vertex*> visited;
    queue<Vertex*> q;
    map<Vertex*, Vertex*> parent;
    
    // start bfs from the starting vertex
    q.push(startVertex);
    visited.insert(startVertex);
    parent[startVertex] = nullptr;
    
    // explore vertices level by level
    while (!q.empty()) {
        Vertex* current = q.front();
        q.pop();
        
        // check if we reached the destination
        if (current == endVertex) {
            // reconstruct path by following parent pointers
            Vertex* node = endVertex;
            while (node != nullptr) {
                path.push_back(node->getValue());
                node = parent[node];
            }
            reverse(path.begin(), path.end());
            return path;
        }
        
        // explore all neighbors of current vertex
        if (adjacencyList.find(current) != adjacencyList.end()) {
            for (auto& neighbor : adjacencyList[current]) {
                Vertex* neighborVertex = neighbor.first;
                
                // mark unvisited neighbor and add to queue
                if (visited.find(neighborVertex) == visited.end()) {
                    visited.insert(neighborVertex);
                    parent[neighborVertex] = current;
                    q.push(neighborVertex);
                }
            }
        }
    }
    
    // no path found between vertices
    return path;
}

// helper method to get vertex by name
Vertex* Graph::getVertex(string name) {
    if (vertexMap.find(name) == vertexMap.end()) {
        return nullptr;
    }
    return vertexMap[name];
}
