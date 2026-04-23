# Graph ADT CLI - Product Requirements Document

## 1. Foundation

This project implements a Graph Abstract Data Type (ADT) representing an undirected weighted graph.

- **Vertex** = location (USF, Starbucks, etc.)
- **Edge** = connection between two locations
- **Label** = distance (weight)

The graph is constructed dynamically from an input file and supports runtime operations through a menu interface.

## 2. Problem

Static graph implementations are limited because:

- Data is hardcoded
- No support for dynamic updates
- Cannot handle arbitrary input structures

This project addresses that by:

- Reading graph data from a file
- Supporting insertion and deletion operations
- Allowing runtime queries such as adjacency and path finding

## 3. Users

| User      | Purpose                                     |
| --------- | ------------------------------------------- |
| CLI user  | Interacts with graph through menu options   |
| Developer | Implements graph logic and structure        |
| Grader    | Verifies correctness using different inputs |

## 4. Core Features

### A. Graph Construction

**Input file:**

```
USF Starbucks Publix Stadium BusStop
USF Starbucks 0.27
USF Publix 2.11
USF Stadium 1.8
Starbucks Stadium 0.32
Starbucks BusStop 8.4
Stadium BusStop 4.72
```

**Internal structure:**

Vertices:

```
{USF, Starbucks, Publix, Stadium, BusStop}
```

Edges:

```
USF = Starbucks (0.27)
USF = Publix (2.11)
USF = Stadium (1.8)
Starbucks = Stadium (0.32)
Starbucks = BusStop (8.4)
Stadium = BusStop (4.72)
```

### B. Graph Operations

- `insertVertex(x)`
- `eraseVertex(v)`
- `insertEdge(v, w, x)`
- `eraseEdge(e)`
- `vertices()`
- `edges()`

### C. Vertex Operations

- `incidentEdges()`
- `isAdjacentTo(v)`

### D. Edge Operations

- `endVertices()`
- `opposite(v)`
- `isAdjacentTo(e)`
- `isIncidentOn(v)`

### E. Menu Interaction

1. Find edges incident on a vertex
2. Find a path in the graph
3. Insert an edge
4. Erase a vertex

### F. Path Finding

**Input:**

- start vertex
- end vertex

**Output:**

```
USF to Starbucks to BusStop
```

**Constraint:**

- Path must contain at least 3 vertices
- Only vertices are printed (no edge weights)

## 5. Inputs / Outputs

### Inputs

**File input:**

- First line = vertices
- Remaining lines = edges + weight

**User input:**

- Vertex names
- Menu selections
- Edge data

### Outputs

**Incident edges:**

```
USF to Starbucks is 0.27 mi
USF to Publix is 2.11 mi
```

**Path:**

```
Starbucks to USF to Stadium
```

**Insert:**

```
Edge inserted
```

**Errors:**

```
Error: vertex not found
Error: edge already exists
```

## 6. Constraints

### Functional Constraints

- Graph is undirected
- No duplicate edges allowed
- Vertices must exist before edge insertion
- Removing a vertex removes all connected edges
- Works for any valid input file

### Structural Constraints

Only one representation must be used:

| Representation   | Suitability             |
| ---------------- | ----------------------- |
| Edge List        | inefficient for queries |
| Adjacency Matrix | high memory usage       |
| Adjacency List   | efficient and flexible  |

**Best choice:** adjacency list

### Performance Constraints

- Path finding should be efficient
- Avoid unnecessary full graph scans
- Operations should scale with input size

## 7. Identify | Setup | Execute

### Identify

- Undirected weighted graph
- Need adjacency queries
- Need traversal for path finding

### Setup

- Vertex class for nodes
- Edge class for connections
- Graph class for full structure
- Adjacency list for storage

### Execute

- Read input file
- Create vertex collection
- Create edge collection
- Build adjacency relationships
- Enable menu-based interaction

## 8. Summary Table

| Component      | Role                         |
| -------------- | ---------------------------- |
| Vertex         | stores location              |
| Edge           | stores connection and weight |
| Graph          | manages entire structure     |
| Adjacency list | stores relationships         |
| Path algorithm | finds valid path             |
| CLI            | user interaction             |
