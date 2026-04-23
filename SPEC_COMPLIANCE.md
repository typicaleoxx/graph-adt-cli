# Graph ADT - Assignment Specification Compliance

## Summary of Changes

All code has been updated to match the assignment requirements exactly.

## Required Classes and Methods

### Vertex Class ✓

- **operator\*()** - Returns vertex name (new)
- **incidentEdges()** - Returns all incident edges (new, per spec)
- **isAdjacentTo(v)** - Checks if adjacent to another vertex ✓
- getValue() - Still available for compatibility ✓

### Edge Class ✓

- **operator\*()** - Returns edge weight/label (new)
- **endVertices()** - Returns pair of endpoints (renamed from getEndVertices) ✓
- **opposite(v)** - Returns other endpoint (renamed from getOtherEndpoint) ✓
- **isAdjacentTo(e)** - Checks if adjacent to another edge (new)
- **isIncidentOn(v)** - Checks if incident on a vertex (new)

### Graph Class ✓

- **vertices()** - Returns all vertices ✓
- **edges()** - Returns all edges ✓
- **insertVertex(x)** - Inserts vertex, prints success message ✓
- **insertEdge(v, w, x)** - Inserts edge, validates and prints "Edge inserted" ✓
- **eraseVertex(v)** - Removes vertex and all edges, prints "Vertex removed" ✓
- **eraseEdge(e)** - Removes edge ✓

## User Interface - Menu System ✓

### Greeting Messages

```
Hello!
Enter the file name:
Thank you. Your graph is ready.
------------
```

### Menu Options (4 only + exit)

```
What would you like to do?
------------
1. Find edges incident on a vertex
2. Find a path in the graph
3. Insert an edge
4. Erase a vertex
0. Exit
```

## Option 1: Incident Edges ✓

- Input: Vertex name
- Output Format: `{vertex} to {neighbor} is {weight} mi`
- Example:
  ```
  USF to Starbucks is 0.27 mi
  USF to Publix is 2.11 mi
  USF to Stadium is 1.8 mi
  ```

## Option 2: Find Path ✓

- Input: Start vertex and end vertex
- Validation: Path must contain at least 3 vertices (NEW - per spec)
- Output Format: `{v1} to {v2} to {v3}...` (vertices only, no edges)
- Example:
  ```
  USF to Starbucks to BusStop
  ```

## Option 3: Insert Edge ✓

- Input: Two vertices and edge label
- Validation: Both vertices must exist, no duplicate edges
- Output: `Edge inserted` on success
- Error messages for validation failures

## Option 4: Erase Vertex ✓

- Input: Vertex name
- Behavior: Removes vertex and all incident edges
- Output: `Vertex removed` on success
- Error messages for invalid vertices

## File Format Support ✓

- Line 1: Space-separated vertex names
- Remaining lines: `vertex1 vertex2 weight` (tab-separated)
- Reads from any input file specified by user

## Test Results

All 4 required menu options tested successfully:

1. **Incident Edges** - Displays all edges from a vertex with correct format
2. **Path Finding** - Finds shortest path (BFS), validates minimum 3 vertices
3. **Insert Edge** - Creates edges between vertices with validation
4. **Erase Vertex** - Removes vertices and connected edges

## Key Implementation Details

- **Representation**: Adjacency list with dynamic objects
- **Graph Type**: Undirected, weighted
- **Path Algorithm**: Breadth-First Search (BFS) for shortest paths
- **Memory Management**: Dynamic allocation with proper cleanup
- **Compilation**: g++ -std=c++11 with no warnings

## Build Instructions

```bash
make              # Compile the project
make clean        # Remove compiled files
./graph_program   # Run the program
```

## Testing

Tested against:

- Input file parsing and graph construction
- All 4 menu operations with various inputs
- Edge cases (empty graphs, single vertices, invalid operations)
- Output format compliance with specification
- Path validation (minimum 3 vertices requirement)
