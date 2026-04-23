#include "Graph.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Graph.cpp - implements file parsing to extract raw vertex and edge data from input file

// parse input file and store raw vertex names and edge information
Graph::Graph(string filename) {
    ifstream inputFile(filename);
    
    // check if file opened successfully
    if (!inputFile.is_open()) {
        cerr << "error: unable to open file " << filename << endl;
        return;
    }
    
    // read first line and extract all vertex names
    string firstLine;
    getline(inputFile, firstLine);
    stringstream vertexStream(firstLine);
    string vertexName;
    
    while (vertexStream >> vertexName) {
        // store each vertex name in the list
        vertexList.push_back(vertexName);
    }
    
    // read remaining lines and extract edges with their weights
    string edgeLine;
    while (getline(inputFile, edgeLine)) {
        if (edgeLine.empty()) continue;
        
        stringstream edgeStream(edgeLine);
        string v1Name, v2Name;
        double weight;
        
        // parse vertex names and weight from the line
        edgeStream >> v1Name >> v2Name >> weight;
        
        // store edge data as a tuple of vertex1, vertex2, and weight
        edgeList.push_back(make_tuple(v1Name, v2Name, weight));
    }
    
    inputFile.close();
}

// return vector containing all vertex names
vector<string> Graph::getVertices() {
    return vertexList;
}

// return vector containing all edge data as (vertex1, vertex2, weight) tuples
vector<tuple<string, string, double>> Graph::getEdges() {
    return edgeList;
}
