#include "Logger.hpp"

#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class MakefileGenerator
{
public:
    static bool make(const fs::path &projectRoot);
};