# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -g

# Linker flags for SFML
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Target executable
TARGET = sfml_collision

# Source files
SRCS = main.cpp

OBJS = $(SRCS:.cpp=.o)

# Build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile the source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: clean

