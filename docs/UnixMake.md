# Makefile for Unix like systems

```
# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -MMD -MP

# Directories
SRCDIR = src
CMDDIR = commands
INCDIR = include
DEPDIR = dependencies
BUILDDIR = ../project-guild-test
OBJDIR = build

# Target executable
TARGET = $(BUILDDIR)/guild

# Find all source files
SRC = $(wildcard $(SRCDIR)/*.cpp)
CMD = $(wildcard $(CMDDIR)/*.cpp)
MAINSRC = main.cpp

# Generate object file names in build directory
OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)
CMDOBJ = $(CMD:%.cpp=$(OBJDIR)/%.o)
MAINOBJ = $(MAINSRC:%.cpp=$(OBJDIR)/%.o)

# Dependency files
DEPS = $(OBJ:.o=.d) $(CMDOBJ:.o=.d) $(MAINOBJ:.o=.d)

# Include directories
INCLUDES = -I./$(DEPDIR) -I./$(INCDIR)

# Default target
all: create_dirs $(TARGET)

# Create necessary directories
create_dirs:
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(OBJDIR)/$(SRCDIR)
	@mkdir -p $(OBJDIR)/$(CMDDIR)

# Link the final executable
$(TARGET): $(MAINOBJ) $(OBJ) $(CMDOBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile main source file
$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Compile source files
$(OBJDIR)/$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Compile command files
$(OBJDIR)/$(CMDDIR)/%.o: $(CMDDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Include dependency files
-include $(DEPS)

# Clean build files
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Clean and rebuild
rebuild: clean all

.PHONY: all clean rebuild create_dirs
```