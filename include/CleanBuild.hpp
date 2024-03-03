#ifndef CLEANBUILD_HPP
#define CLEANBUILD_HPP

#include <filesystem>
#include <fstream>
#include <cstdlib>

#include "Logger.hpp"
#include "nlohmann/json.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

void cleanBuild();

#endif // CLEANBUILD_HPP