# Graph ADT - Programming Project 4

## Overview

This project implements a **Graph Abstract Data Type (ADT)** for an undirected weighted graph with a command-line interface for interactive graph manipulation and queries.

**Implementation**: C++11 with adjacency list representation  
**Tested**: All 4 menu operations verified ✓

## Features Implemented

### Core Data Structures

- **Vertex Class** - Represents graph nodes with incident edge tracking
- **Edge Class** - Represents weighted connections between vertices
- **Graph Class** - Manages vertices, edges, and graph operations

### Required Methods (Per Specification)

#### Vertex

- `operator*()` - Returns vertex name
- `incidentEdges()` - Returns all connected edges
- `isAdjacentTo(v)` - Checks if adjacent to another vertex

#### Edge

- `operator*()` - Returns edge weight
- `endVertices()` - Returns pair of endpoints
- `opposite(v)` - Returns other endpoint
- `isAdjacentTo(e)` - Checks if adjacent to another edge
- `isIncidentOn(v)` - Checks if incident on a vertex

#### Graph

- `vertices()` - Returns all vertices
- `edges()` - Returns all edges
- `insertVertex(x)` - Adds a new vertex
- `insertEdge(v, w, x)` - Adds weighted edge with validation
- `eraseVertex(v)` - Removes vertex and all incident edges
- `eraseEdge(v, w)` - Removes edge between vertices

## Building and Running

### Compile

```bash
g++ -std=c++11 -o graph_program main.cpp Graph.cpp Vertex.cpp Edge.cpp
```

### Run

```bash
./graph_program   # Start the interactive program
```

### Input

- Enter input file name when prompted
- File format:
  - Line 1: Space-separated vertex names
  - Remaining lines: `vertex1 vertex2 weight` (tab-separated)

## Menu Options

### Greeting

```
Hello!
Enter the file name: input.txt
Thank you. Your graph is ready.
```

### Main Menu

```
What would you like to do?
------------
1. Find edges incident on a vertex
2. Find a path in the graph
3. Insert an edge
4. Erase a vertex
0. Exit
```

### Option 1: Incident Edges

**Purpose**: Find all edges connected to a vertex

**Input**: Vertex name

**Output Format**:

```
USF to Starbucks is 0.27 mi
USF to Publix is 2.11 mi
USF to Stadium is 1.8 mi
```

### Option 2: Find Path

**Purpose**: Find a path between two vertices using BFS

**Input**: Start vertex and end vertex

**Constraints**:

- Both vertices must exist
- Start and end must be different
- Path must contain at least 3 vertices (specification requirement)

**Output Format**: `vertex1 to vertex2 to vertex3...` (vertices only, no edges)

### Option 3: Insert Edge

**Purpose**: Add a new weighted edge between vertices

**Input**:

- First vertex name
- Second vertex name
- Edge weight (positive number)

**Validation**:

- Both vertices must exist
- No duplicate edges allowed
- Weight must be positive

**Output**: `Edge inserted` on success

### Option 4: Erase Vertex

**Purpose**: Remove a vertex and all its connected edges

**Input**: Vertex name to remove

**Output**: `Vertex removed` on success

## Sample Input File Format

**File: input.txt**

```
USF Starbucks Publix Stadium BusStop
USF Starbucks 0.27
USF Publix 2.11
USF Stadium 1.8
Starbucks Stadium 0.32
Starbucks BusStop 8.4
Stadium BusStop 4.72
```

**Vertices**: 5 (USF, Starbucks, Publix, Stadium, BusStop)  
**Edges**: 6 (all undirected, weighted)

## Test Results Summary

| Test Case          | Input                | Expected                    | Result |
| ------------------ | -------------------- | --------------------------- | ------ |
| Greeting           | -                    | Hello! + Thank you message  | ✓ PASS |
| Menu Display       | -                    | 4 options + exit            | ✓ PASS |
| Incident Edges     | USF                  | 3 edges with format         | ✓ PASS |
| Path (2 vertices)  | USF→Starbucks        | Error: min 3 vertices       | ✓ PASS |
| Path (3+ vertices) | USF→BusStop          | USF to Starbucks to BusStop | ✓ PASS |
| Insert Edge        | Publix-BusStop (5.5) | Edge inserted               | ✓ PASS |
| Erase Vertex       | Stadium              | Vertex removed              | ✓ PASS |
| Error Handling     | InvalidVertex        | error: vertex not found     | ✓ PASS |

## Code Quality

- **Memory Management**: Dynamic allocation with proper cleanup in destructor
- **Error Handling**: Comprehensive validation for all operations
- **Algorithm**: Breadth-First Search (BFS) for shortest path finding
- **Compilation**: No warnings with `-Wall` flag
- **Code Style**: Student-style comments, clear variable names, modular design

## File Structure

```
.
├── Graph.h / Graph.cpp        # Main graph class
├── Vertex.h / Vertex.cpp      # Vertex representation
├── Edge.h / Edge.cpp          # Edge representation
├── main.cpp                   # Interactive menu
└── input.txt                  # Sample test data
```

## Specification Compliance

This implementation fully matches the assignment specification PP4:

- ✓ Undirected weighted graph
- ✓ Adjacency list representation
- ✓ Required class methods implemented
- ✓ 4-option menu system
- ✓ All output formats match specification
- ✓ File-based graph construction
- ✓ Path finding with BFS
- ✓ Error handling and validation

## Running Tests

```bash
# First compile
g++ -std=c++11 -o graph_program main.cpp Graph.cpp Vertex.cpp Edge.cpp

# Test greeting and menu
echo -e "input.txt\n0" | ./graph_program

# Test incident edges
echo -e "input.txt\n1\nUSF\n0" | ./graph_program

# Test path finding (3+ vertices)
echo -e "input.txt\n2\nUSF\nBusStop\n0" | ./graph_program

# Test insert edge
echo -e "input.txt\n3\nPublix\nBusStop\n5.5\n0" | ./graph_program

# Test erase vertex
echo -e "input.txt\n4\nStadium\n0" | ./graph_program
```
