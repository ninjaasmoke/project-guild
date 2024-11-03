#include "Logger.hpp"

#include <fstream>
#include <string>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

class MakefileGenerator
{
public:
    static bool make(const fs::path &projectRoot);
};