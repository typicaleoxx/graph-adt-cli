#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include <iostream>
#include <string>

using namespace std;

// main.cpp - provides interactive menu interface for users to perform graph operations

// display menu options and get user choice with validation
int showMenu() {
    cout << "\nWhat would you like to do?" << endl;
    cout << "------------" << endl;
    cout << "1. Find edges incident on a vertex" << endl;
    cout << "2. Find a path in the graph" << endl;
    cout << "3. Insert an edge" << endl;
    cout << "4. Erase a vertex" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
    
    int choice;
    // validate input is a valid integer
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "error: invalid input" << endl;
        return -1;
    }
    cin.ignore();
    return choice;
}

// handle finding and displaying edges connected to a vertex
void handleIncidentEdges(Graph* graph) {
    cout << "Enter vertex name: ";
    string vertex;
    getline(cin, vertex);
    
    // validate vertex name is not empty
    if (vertex.empty()) {
        cout << "error: vertex name cannot be empty" << endl;
        return;
    }
    
    // get all incident edges for the vertex
    vector<Edge*> edges = graph->incidentEdges(vertex);
    
    if (edges.empty()) {
        cout << "No edges found for vertex " << vertex << endl;
        return;
    }
    
    cout << "Edges incident on " << vertex << ":" << endl;
    // display each edge with its weight in formatted output
    for (Edge* edge : edges) {
        pair<Vertex*, Vertex*> endpoints = edge->endVertices();
        Vertex* other = (endpoints.first->getValue() == vertex) ? endpoints.second : endpoints.first;
        cout << vertex << " to " << other->getValue() << " is " << **edge << " mi" << endl;
    }
}

// handle finding path between two vertices with validation
void handlePathFinding(Graph* graph) {
    cout << "Enter start vertex: ";
    string start;
    getline(cin, start);
    
    cout << "Enter end vertex: ";
    string end;
    getline(cin, end);
    
    // validate vertex names are not empty
    if (start.empty() || end.empty()) {
        cout << "error: vertex names cannot be empty" << endl;
        return;
    }
    
    // validate start and end are different
    if (start == end) {
        cout << "error: start and end vertices must be different" << endl;
        return;
    }
    
    // find path using bfs algorithm
    vector<string> path = graph->findPath(start, end);
    
    // display path if found, and validate it has at least 3 vertices
    if (path.empty()) {
        cout << "No path found between " << start << " and " << end << endl;
        return;
    }
    
    // validate path has at least 3 vertices per spec
    if (path.size() < 3) {
        cout << "error: path must contain at least 3 vertices" << endl;
        return;
    }
    
    // print path in format: vertex to vertex to vertex
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) cout << " to ";
    }
    cout << endl;
}

// handle inserting new edge between two vertices with validation
void handleInsertEdge(Graph* graph) {
    cout << "Enter first vertex: ";
    string v1;
    getline(cin, v1);
    
    cout << "Enter second vertex: ";
    string v2;
    getline(cin, v2);
    
    // validate vertex names are not empty
    if (v1.empty() || v2.empty()) {
        cout << "error: vertex names cannot be empty" << endl;
        return;
    }
    
    // validate vertices are different
    if (v1 == v2) {
        cout << "error: cannot create self-loop" << endl;
        return;
    }
    
    cout << "Enter edge weight: ";
    double weight;
    
    // validate weight input
    if (!(cin >> weight)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "error: invalid weight input" << endl;
        return;
    }
    cin.ignore();
    
    // validate weight is positive
    if (weight < 0) {
        cout << "error: weight cannot be negative" << endl;
        return;
    }
    
    // add edge to the graph
    graph->insertEdge(v1, v2, weight);
}

// handle removing a vertex and its connected edges with validation
void handleEraseVertex(Graph* graph) {
    cout << "Enter vertex name to erase: ";
    string vertex;
    getline(cin, vertex);
    
    // validate vertex name is not empty
    if (vertex.empty()) {
        cout << "error: vertex name cannot be empty" << endl;
        return;
    }
    
    // remove vertex from the graph
    graph->eraseVertex(vertex);
}

// main entry point that initializes graph and runs menu loop with error handling
int main() {
    // display welcome message
    cout << "Hello!" << endl;
    
    string filename;
    cout << "Enter the file name: ";
    getline(cin, filename);
    
    // validate filename is not empty
    if (filename.empty()) {
        cerr << "error: filename cannot be empty" << endl;
        return 1;
    }
    
    // create graph by reading from file
    Graph* graph = new Graph(filename);
    
    // display ready message
    cout << "Thank you. Your graph is ready." << endl;
    cout << "------------" << endl;
    
    // main menu loop for user interaction
    while (true) {
        int choice = showMenu();
        
        // validate menu choice
        if (choice == -1) {
            continue;
        }
        
        switch (choice) {
            case 1:
                handleIncidentEdges(graph);
                break;
            case 2:
                handlePathFinding(graph);
                break;
            case 3:
                handleInsertEdge(graph);
                break;
            case 4:
                handleEraseVertex(graph);
                break;
            case 0:
                // exit program
                cout << "Exiting..." << endl;
                delete graph;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    
    return 0;
}
