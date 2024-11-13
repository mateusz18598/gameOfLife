# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Target executable name
TARGET = main.exe

# Find all .cpp and .h files
SRCS = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)

# Object files generated from .cpp files
OBJS = $(SRCS:.cpp=.o)

# Default rule to build the target
all: $(TARGET)

# Rule to link object files and create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files into .o files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	del -f $(OBJS) $(TARGET)

# Phony targets to avoid conflicts with files named 'clean' or 'all'
.PHONY: all clean
