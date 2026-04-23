# Implementation Phases

## 1. Foundation

Each phase defines:

- which files are worked on
- which functions are implemented
- what output is expected

This keeps the system modular and prevents mixing responsibilities.

## 2. Phase Flow Overview

| Phase   | Task             | Files              |
| ------- | ---------------- | ------------------ |
| Phase 1 | Parsing          | Graph files        |
| Phase 2 | Core Classes     | Vertex, Edge files |
| Phase 3 | Graph Build      | Graph files        |
| Phase 4 | Modifications    | Graph files        |
| Phase 5 | Queries and Path | Graph files        |
| Phase 6 | Menu             | main file          |
| Phase 7 | Validation       | all relevant files |

## 3. Deep Breakdown

### Phase 1: File Parsing

**Files**

- Graph.h
- Graph.cpp

**Functions**

- Graph(filename)

**Responsibilities**

- open file
- read first line to extract vertices
- read remaining lines to extract edges

**Output**

- raw vertex list
- raw edge list

### Phase 2: Core Classes (Vertex and Edge)

**Files**

- Vertex.h
- Vertex.cpp
- Edge.h
- Edge.cpp

**Functions**

Vertex

- operator\*()
- incidentEdges()
- isAdjacentTo(v)

Edge

- operator\*()
- endVertices()
- opposite(v)
- isAdjacentTo(e)
- isIncidentOn(v)

**Responsibilities**

- define structure of vertex and edge
- implement their behaviors independently of Graph

**Output**

- fully functional Vertex and Edge classes

### Phase 3: Graph Construction

**Files**

- Graph.h
- Graph.cpp

**Functions**

- vertices()
- edges()

**Responsibilities**

- create vertex collection
- create edge collection
- build adjacency list

**Core Logic**

```
for each edge (v, u):
    adjacency[v].add(u)
    adjacency[u].add(v)
```

**Output**

- fully constructed graph

### Phase 4: Graph Modification

**Files**

- Graph.cpp

**Functions**

- insertVertex(x)
- insertEdge(v, w, x)
- eraseVertex(v)
- eraseEdge(e)

**Responsibilities**

insertVertex

- check if vertex exists
- insert if not present

insertEdge

- validate both vertices exist
- check for duplicate edge
- insert edge and update adjacency

eraseVertex

- remove vertex
- remove all incident edges
- update adjacency list

eraseEdge

- remove edge
- update adjacency

**Output**

- graph supports dynamic updates

### Phase 5: Query and Path Logic

**Files**

- Graph.cpp

**Functions**

- incidentEdges()
- isAdjacentTo(v)
- path finding logic (BFS)

**Responsibilities**

Incident Edges

- lookup adjacency list
- print all connected edges

Adjacency Check

- verify if two vertices are neighbors

Path Finding

- start from source
- use queue
- mark visited
- store parent
- reach destination
- reconstruct path

**Output**

- correct queries
- valid paths between vertices

### Phase 6: Menu System

**Files**

- main.cpp

**Functions**

- main()
- menu loop

**Responsibilities**

- display menu
- read input
- call graph functions
- print results

**Output**

- interactive program

### Phase 7: Validation and Error Handling

**Files**

- Graph.cpp
- main.cpp

**Responsibilities**

Handle cases:

- vertex not found
- duplicate edge
- invalid input
- no valid path

**Output**

- stable and error-safe system

## 4. Implementation Summary Table

| Phase   | Files                    | Key Functions                 |
| ------- | ------------------------ | ----------------------------- |
| Phase 1 | Graph.h, Graph.cpp       | constructor                   |
| Phase 2 | Vertex.h/cpp, Edge.h/cpp | all vertex and edge methods   |
| Phase 3 | Graph.h, Graph.cpp       | vertices(), edges()           |
| Phase 4 | Graph.cpp                | insert and erase functions    |
| Phase 5 | Graph.cpp                | queries and BFS               |
| Phase 6 | main.cpp                 | menu system                   |
| Phase 7 | Graph.cpp, main.cpp      | validation and error handling |
