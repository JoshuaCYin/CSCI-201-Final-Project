# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Executable name
EXECUTABLE = main

# Include directories
INCLUDES = -I$(INC_DIR)

# Main target
all: $(EXECUTABLE)

# Link the program
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE)

# Phony targets
.PHONY: all clean

# Include dependencies
-include $(OBJECTS:.o=.d)

# Generate dependency files
$(OBJ_DIR)/%.d: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -MM -MT '$(OBJ_DIR)/$*.o $@' $< > $@