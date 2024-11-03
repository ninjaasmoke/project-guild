#include "MakefileGenerator.h"

namespace fs = std::filesystem;

const char *embeddedMakefile = R"""(
# Detect OS
ifeq ($(OS),Windows_NT)
	detected_OS := Windows
	# Windows-specific settings
	RM := rmdir /s /q
	MKDIR = if not exist "$1" mkdir "$1"
	RMFILE := del /q
	SEP := \\
	EXE := .exe
	CONSOLE_FLAG := -mconsole
else
	detected_OS := $(shell uname -s)
	# Unix-specific settings
	RM := rm -rf
	MKDIR = mkdir -p "$1"
	RMFILE := rm -f
	SEP := /
	EXE :=
	CONSOLE_FLAG :=
endif

# Compiler settings
CXX := g++
CC := gcc
CXXFLAGS := -std=c++17 -Wall -Wextra $(CONSOLE_FLAG)
CFLAGS := -Wall -Wextra

# Directories
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := .build
BIN_DIR := .bin
PACKAGES_DIR := packages

# Source files
MAIN_SRC := main.cpp
CPP_SRCS := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp)
C_SRCS := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
PKG_CPP_SRCS := $(wildcard $(PACKAGES_DIR)/*/*.cpp) $(wildcard $(PACKAGES_DIR)/*/*/*.cpp)
PKG_C_SRCS := $(wildcard $(PACKAGES_DIR)/*/*.c) $(wildcard $(PACKAGES_DIR)/*/*/*.c)

# Generate object file names
MAIN_OBJ := $(BUILD_DIR)/main.o
OBJS := $(subst $(SRC_DIR)/,$(BUILD_DIR)/,$(CPP_SRCS:.cpp=.o))
OBJS += $(subst $(SRC_DIR)/,$(BUILD_DIR)/,$(C_SRCS:.c=.o))
OBJS += $(subst $(PACKAGES_DIR)/,$(BUILD_DIR)/packages/,$(PKG_CPP_SRCS:.cpp=.o))
OBJS += $(subst $(PACKAGES_DIR)/,$(BUILD_DIR)/packages/,$(PKG_C_SRCS:.c=.o))

# Include directories
INCLUDE_PATHS := -I$(INCLUDE_DIR)
INCLUDE_PATHS += $(foreach dir,$(wildcard $(PACKAGES_DIR)/*/),-I$(dir)include)

# Output executable
TARGET := $(BIN_DIR)/main$(EXE)

# Default target
all: $(TARGET)

# Rule to create build directories
$(BUILD_DIR):
	$(call MKDIR,$(BUILD_DIR))
	$(call MKDIR,$(BUILD_DIR)$(SEP)packages)

$(BIN_DIR):
	$(call MKDIR,$(BIN_DIR))

# Rules for creating directories
$(shell $(call MKDIR,$(BUILD_DIR)))
$(shell $(call MKDIR,$(BUILD_DIR)$(SEP)packages))
$(shell $(call MKDIR,$(BIN_DIR)))

# Rule for compiling main.cpp
$(MAIN_OBJ): $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATHS) -c $< -o $@

# Rules for compiling source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(call MKDIR,$(dir $@))
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATHS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@$(call MKDIR,$(dir $@))
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@

# Rules for compiling package source files
$(BUILD_DIR)/packages/%.o: $(PACKAGES_DIR)/%.cpp
	@$(call MKDIR,$(dir $@))
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATHS) -c $< -o $@

$(BUILD_DIR)/packages/%.o: $(PACKAGES_DIR)/%.c
	@$(call MKDIR,$(dir $@))
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@

# Link everything together
$(TARGET): $(MAIN_OBJ) $(OBJS)
	$(CXX) $(MAIN_OBJ) $(OBJS) -o $(TARGET)

# Clean built files
clean:
	-$(RM) "$(BUILD_DIR)"
	-$(RM) "$(BIN_DIR)"

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run help

# Display help information
help:
	@echo "Operating System: $(detected_OS)"
	@echo "Available targets:"
	@echo "  all    - Build the project (default)"
	@echo "  clean  - Remove build files"
	@echo "  run    - Build and run the project"
	@echo "  help   - Display this help message"

# Debug target to show detected files
show-files:
	@echo "Operating System: $(detected_OS)"
	@echo "Main Source: $(MAIN_SRC)"
	@echo "Main Object: $(MAIN_OBJ)"
	@echo "C++ Sources: $(CPP_SRCS)"
	@echo "C Sources: $(C_SRCS)"
	@echo "Package C++ Sources: $(PKG_CPP_SRCS)"
	@echo "Package C Sources: $(PKG_C_SRCS)"
	@echo "Objects: $(OBJS)"
	@echo "Include Paths: $(INCLUDE_PATHS)" 
)""";

bool MakefileGenerator::make(const fs::path &projectRoot)
{
    try
    {
        fs::path destPath = projectRoot / "Makefile";
        std::ofstream outFile(destPath);
        if (!outFile)
        {
            Logger::error("Failed to create destination Makefile at: " + destPath.string());
            return false;
        }
        outFile << embeddedMakefile;
        outFile.close();
        return true;
    }
    catch (const std::exception &e)
    {
        Logger::error("Error writing Makefile: " + std::string(e.what()));
        return false;
    }
}