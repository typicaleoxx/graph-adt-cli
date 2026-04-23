CXX = g++
CXXFLAGS = -std=c++11 -Wall
SOURCES = main.cpp Graph.cpp Vertex.cpp Edge.cpp
HEADERS = Graph.h Vertex.h Edge.h
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = graph_program

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all clean run
