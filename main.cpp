#include "Graph.h"
#include <iostream>
#include <string>

using namespace std;

// main.cpp - provides interactive menu interface for users to perform graph operations

// display menu options and get user choice
int showMenu() {
    cout << "\n=== Graph Menu ===" << endl;
    cout << "1. Find edges incident on a vertex" << endl;
    cout << "2. Find a path in the graph" << endl;
    cout << "3. Insert an edge" << endl;
    cout << "4. Erase a vertex" << endl;
    cout << "5. Insert a vertex" << endl;
    cout << "6. Erase an edge" << endl;
    cout << "7. Display all vertices" << endl;
    cout << "8. Check if vertices are adjacent" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
    
    int choice;
    cin >> choice;
    cin.ignore();
    return choice;
}

// handle finding and displaying edges connected to a vertex
void handleIncidentEdges(Graph* graph) {
    cout << "Enter vertex name: ";
    string vertex;
    getline(cin, vertex);
    
    // get all incident edges for the vertex
    vector<Edge*> edges = graph->incidentEdges(vertex);
    
    if (edges.empty()) {
        cout << "No edges found for vertex " << vertex << endl;
        return;
    }
    
    cout << "Edges incident on " << vertex << ":" << endl;
    // display each edge with its weight in formatted output
    for (Edge* edge : edges) {
        pair<Vertex*, Vertex*> endpoints = edge->getEndVertices();
        Vertex* other = (endpoints.first->getValue() == vertex) ? endpoints.second : endpoints.first;
        cout << vertex << " to " << other->getValue() << " is " << edge->getLabel() << " mi" << endl;
    }
}

// handle finding path between two vertices
void handlePathFinding(Graph* graph) {
    cout << "Enter start vertex: ";
    string start;
    getline(cin, start);
    
    cout << "Enter end vertex: ";
    string end;
    getline(cin, end);
    
    // find path using bfs algorithm
    vector<string> path = graph->findPath(start, end);
    
    // display path if found
    if (path.empty()) {
        cout << "No path found between " << start << " and " << end << endl;
        return;
    }
    
    cout << "Path from " << start << " to " << end << ": ";
    // print each vertex in the path separated by arrows
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) cout << " to ";
    }
    cout << endl;
}

// handle inserting new edge between two vertices
void handleInsertEdge(Graph* graph) {
    cout << "Enter first vertex: ";
    string v1;
    getline(cin, v1);
    
    cout << "Enter second vertex: ";
    string v2;
    getline(cin, v2);
    
    cout << "Enter edge weight: ";
    double weight;
    cin >> weight;
    cin.ignore();
    
    // add edge to the graph
    graph->insertEdge(v1, v2, weight);
    cout << "Edge inserted" << endl;
}

// handle removing a vertex and its connected edges
void handleEraseVertex(Graph* graph) {
    cout << "Enter vertex name to erase: ";
    string vertex;
    getline(cin, vertex);
    
    // remove vertex from the graph
    graph->eraseVertex(vertex);
    cout << "Vertex erased" << endl;
}

// handle inserting new vertex into the graph
void handleInsertVertex(Graph* graph) {
    cout << "Enter vertex name: ";
    string vertex;
    getline(cin, vertex);
    
    // add vertex to the graph
    graph->insertVertex(vertex);
    cout << "Vertex inserted" << endl;
}

// handle removing specific edge between two vertices
void handleEraseEdge(Graph* graph) {
    cout << "Enter first vertex: ";
    string v1;
    getline(cin, v1);
    
    cout << "Enter second vertex: ";
    string v2;
    getline(cin, v2);
    
    // remove edge from the graph
    graph->eraseEdge(v1, v2);
    cout << "Edge erased" << endl;
}

// handle displaying all vertices in the graph
void handleDisplayVertices(Graph* graph) {
    vector<Vertex*> vertices = graph->vertices();
    
    cout << "Vertices in graph:" << endl;
    // print each vertex name
    for (Vertex* v : vertices) {
        cout << v->getValue() << endl;
    }
}

// handle checking adjacency between two vertices
void handleCheckAdjacency(Graph* graph) {
    cout << "Enter first vertex: ";
    string v1;
    getline(cin, v1);
    
    cout << "Enter second vertex: ";
    string v2;
    getline(cin, v2);
    
    // check if vertices are neighbors
    bool adjacent = graph->isAdjacentTo(v1, v2);
    
    if (adjacent) {
        cout << v1 << " and " << v2 << " are adjacent" << endl;
    } else {
        cout << v1 << " and " << v2 << " are not adjacent" << endl;
    }
}

// main entry point that initializes graph and runs menu loop
int main() {
    string filename;
    cout << "Enter input file name: ";
    getline(cin, filename);
    
    // create graph by reading from file
    Graph* graph = new Graph(filename);
    
    // display welcome message
    cout << "Graph loaded successfully!" << endl;
    
    // main menu loop for user interaction
    while (true) {
        int choice = showMenu();
        
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
            case 5:
                handleInsertVertex(graph);
                break;
            case 6:
                handleEraseEdge(graph);
                break;
            case 7:
                handleDisplayVertices(graph);
                break;
            case 8:
                handleCheckAdjacency(graph);
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
