# In-Memory Database Engine Makefile
# Author: Database Engine Team
# Version: 1.0

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g
TARGET = database_engine
SRCDIR = src
INCDIR = include
TESTDIR = tests
EXAMPLEDIR = examples
DOCSDIR = docs

# Source files
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/database.cpp $(SRCDIR)/table.cpp $(SRCDIR)/index.cpp
HEADERS = $(INCDIR)/database.h $(INCDIR)/table.h $(INCDIR)/index.h

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Build the main executable
$(TARGET): $(OBJECTS)
	@echo "Linking $(TARGET)..."
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "Build complete! Run './$(TARGET)' to start the database engine."

# Compile source files
$(SRCDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Clean build files
clean:
	@echo "Cleaning build files..."
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean complete."

# Run the database engine
run: $(TARGET)
	@echo "Starting Database Engine..."
	./$(TARGET)

# Run basic tests
test: $(TARGET)
	@echo "Running basic functionality tests..."
	@echo "=== Basic Operations Test ==="
	@./$(TARGET) < $(TESTDIR)/basic_operations.sql
	@echo "\n=== Advanced Operations Test ==="
	@./$(TARGET) < $(TESTDIR)/advanced_operations.sql

# Run example demos
demo: $(TARGET)
	@echo "Running demonstration examples..."
	@echo "=== University Database Demo ==="
	@./$(TARGET) < $(EXAMPLEDIR)/university_demo.sql
	@echo "\n=== E-commerce Database Demo ==="
	@./$(TARGET) < $(EXAMPLEDIR)/ecommerce_demo.sql

# Performance test with large dataset
perf-test: $(TARGET)
	@echo "Running performance tests..."
	@echo "This will create and query large datasets..."
	@./$(TARGET) < $(TESTDIR)/performance_test.sql

# Install (copy to /usr/local/bin)
install: $(TARGET)
	@echo "Installing $(TARGET) to /usr/local/bin..."
	sudo cp $(TARGET) /usr/local/bin/
	@echo "Installation complete. You can now run '$(TARGET)' from anywhere."

# Uninstall
uninstall:
	@echo "Removing $(TARGET) from /usr/local/bin..."
	sudo rm -f /usr/local/bin/$(TARGET)
	@echo "Uninstallation complete."

# Create project structure (for development setup)
setup:
	@echo "Setting up project structure..."
	mkdir -p $(SRCDIR) $(INCDIR) $(TESTDIR) $(EXAMPLEDIR) $(DOCSDIR)
	@echo "Project structure created."

# Debug build
debug: CXXFLAGS += -DDEBUG -g3 -O0
debug: $(TARGET)
	@echo "Debug build complete. Use gdb ./$(TARGET) for debugging."

# Release build
release: CXXFLAGS += -DNDEBUG -O3
release: clean $(TARGET)
	@echo "Release build complete."

# Check for memory leaks (requires valgrind)
memcheck: $(TARGET)
	@echo "Running memory leak check..."
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET) < $(TESTDIR)/basic_operations.sql

# Generate documentation (requires doxygen)
docs:
	@echo "Generating documentation..."
	doxygen Doxyfile
	@echo "Documentation generated in $(DOCSDIR)/html/"

# Show help
help:
	@echo "Available targets:"
	@echo "  all       - Build the database engine (default)"
	@echo "  clean     - Remove build files"
	@echo "  run       - Build and run the database engine"
	@echo "  test      - Run automated tests"
	@echo "  demo      - Run demonstration examples"
	@echo "  perf-test - Run performance tests"
	@echo "  debug     - Build with debug symbols"
	@echo "  release   - Build optimized release version"
	@echo "  install   - Install to system PATH"
	@echo "  uninstall - Remove from system PATH"
	@echo "  memcheck  - Check for memory leaks (requires valgrind)"
	@echo "  docs      - Generate documentation (requires doxygen)"
	@echo "  setup     - Create project directory structure"
	@echo "  help      - Show this help message"

.PHONY: all clean run test demo perf-test install uninstall setup debug release memcheck docs help