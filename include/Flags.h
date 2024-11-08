// Flags.h
#pragma once
#include <string>
#include <map>

struct Flag
{
    std::string name;
    std::string value;
    bool hasValue;
};

// Type alias for convenience
using FlagMap = std::map<std::string, Flag>;

// Function declarations
FlagMap parseFlags(int argc, char *argv[]);