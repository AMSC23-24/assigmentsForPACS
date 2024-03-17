# Makefile for compiling a1.cpp

# Compiler settings - Can change to clang++ if you prefer
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11 -g

# Build target
TARGET = a1

# Default make
all: $(TARGET)

# Rule for building the target
$(TARGET): a1.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) a1.cpp

# Clean build files
clean:
	rm -f $(TARGET)
