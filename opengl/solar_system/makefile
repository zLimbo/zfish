CXX := g++ -std=c++11
EXEC := SolarSystem
SOURCES := $(wildcard *.cpp)
HEADER_PP := $(wildcard *.hpp)
OBJECTS := $(SOURCES:.cpp=.o)
LDFLAGS := -lglut -lGL -lGLU

all:
	$(CXX) $(SOURCES) $(LDFLAGS) -o $(EXEC)

.PHONY: clean
clean:
	rm -rf $(EXEC) $(OBJECTS)
