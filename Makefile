# Compiler settings
SSL_DIR = C:/Program Files/OpenSSL-Win64

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -MMD -MP -DCPPHTTPLIB_OPENSSL_SUPPORT
LDFLAGS = -lWs2_32 -L"$(SSL_DIR)/lib" -lssl -lcrypto

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
INCLUDES = -I./$(DEPDIR) -I./$(INCDIR) -I"$(SSL_DIR)/include"

# Default target
all: create_dirs $(TARGET)

# Create necessary directories
create_dirs:
	@if not exist "$(BUILDDIR)" mkdir "$(BUILDDIR)"
	@if not exist "$(OBJDIR)\$(SRCDIR)" mkdir "$(OBJDIR)\$(SRCDIR)"
	@if not exist "$(OBJDIR)\$(CMDDIR)" mkdir "$(OBJDIR)\$(CMDDIR)"

# Link the final executable
$(TARGET): $(MAINOBJ) $(OBJ) $(CMDOBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

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
	@if exist "$(OBJDIR)" rmdir /s /q "$(OBJDIR)"
	@if exist "$(TARGET)" del "$(TARGET)"

# Clean and rebuild
rebuild: clean all

.PHONY: all clean rebuild create_dirs