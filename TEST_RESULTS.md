# Graph ADT CLI - Testing Summary

## Project Status: COMPLETE ✓

All 7 phases implemented and tested successfully.

## Test Results

### Phase 1: File Parsing ✓

- Successfully reads graph data from input file
- Extracts vertices from first line
- Extracts edges with weights from remaining lines
- Error handling for missing/invalid files

### Phase 2: Core Classes ✓

- Vertex class: stores node name, manages incident edges
- Edge class: stores endpoints and weight
- Both classes fully functional with getter methods

### Phase 3: Graph Construction ✓

- Graph loads vertices and edges from file
- Adjacency list built correctly
- All data structures initialized properly

### Phase 4: Graph Modification ✓

- insertVertex: adds new vertices
- insertEdge: creates edges between vertices (tested with Stadium-Publix edge)
- eraseVertex: removes vertices and connected edges
- eraseEdge: removes specific edges
- All operations update internal structures correctly

### Phase 5: Query and Path Logic ✓

- incidentEdges: displays all edges from a vertex (tested with USF)
  - Output: USF to Starbucks 0.27 mi, USF to Publix 2.11 mi, USF to Stadium 1.8 mi
- isAdjacentTo: checks vertex connectivity (tested USF-Starbucks = adjacent)
- findPath (BFS): finds shortest path between vertices
  - Test: Starbucks to BusStop = "Starbucks to BusStop"

### Phase 6: Menu System ✓

- Menu displays 8 operations + exit
- All 8 operations fully functional
- Clean, user-friendly interface

### Phase 7: Validation and Error Handling ✓

- Input validation on all user inputs
- Error messages for invalid operations
- Graph construction validates file format, duplicate vertices/edges, negative weights
- Menu validates numeric input

## Build Instructions

```bash
make                    # compile the project
make clean             # remove compiled files
make run               # compile and run
```

## Testing Commands

```bash
# Display all vertices
echo -e "input.txt\n7\n0" | ./graph_program

# Find incident edges on USF
echo -e "input.txt\n1\nUSF\n0" | ./graph_program

# Find path from Starbucks to BusStop
echo -e "input.txt\n2\nStarbucks\nBusStop\n0" | ./graph_program

# Check adjacency between USF and Starbucks
echo -e "input.txt\n8\nUSF\nStarbucks\n0" | ./graph_program

# Insert new vertex Library
echo -e "input.txt\n5\nLibrary\n7\n0" | ./graph_program

# Insert edge between Stadium and Publix with weight 3.5
echo -e "input.txt\n3\nStadium\nPublix\n3.5\n0" | ./graph_program
```

## Graph Structure (input.txt)

Vertices: USF, Starbucks, Publix, Stadium, BusStop

Edges:

- USF ↔ Starbucks (0.27 mi)
- USF ↔ Publix (2.11 mi)
- USF ↔ Stadium (1.8 mi)
- Starbucks ↔ Stadium (0.32 mi)
- Starbucks ↔ BusStop (8.4 mi)
- Stadium ↔ BusStop (4.72 mi)

## Files in Repository

- Graph.h / Graph.cpp - Main graph class with all operations
- Vertex.h / Vertex.cpp - Vertex class implementation
- Edge.h / Edge.cpp - Edge class implementation
- main.cpp - Interactive menu system
- Makefile - Build automation
- input.txt - Sample graph data
- PRD.md - Product requirements document
- PHASES.md - Implementation phases documentation
