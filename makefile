# Compiler and flags
CXX = clang++               # Use clang++ as the compiler
CXXFLAGS = -std=c++17 -Wall -Wextra  # Compilation flags
LDFLAGS =  -lssl -lcrypto                 # Linking flags (if any)

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Name of the final executable
EXEC = bin/gitt

# Default target: build the executable
all: $(EXEC)

# Rule to link object files into the final executable
$(EXEC): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)  # Ensure the bin directory exists
	$(CXX) $(LDFLAGS) $^ -o $@

# Rule to compile .cpp files to .o object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)  # Ensure the object directory exists
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the generated files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
