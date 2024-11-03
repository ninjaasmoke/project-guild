#ifndef CREATEGUILDFS_HPP
#define CREATEGUILDFS_HPP

#include <string>
#include <filesystem>
#include <fstream>
#include <system_error>
#include <vector>
#include <iostream>


#include "GetCurrentFolder.hpp"
#include "MakefileGenerator.h"
#include "nlohmann/json.hpp"

void createGuildStructure(const std::string &projectName);
bool createRootFolder(const std::filesystem::path &projectName);
bool createSubfolders(const std::filesystem::path &rootPath);
bool createDepJson(const std::filesystem::path &rootPath, const std::string &projectName);
bool createSampleHeaderFiles(const std::filesystem::path &rootPath);
bool createSampleSourceFiles(const std::filesystem::path &rootPath);
bool createMainCpp(const std::filesystem::path &rootPath, const std::string &projectName);

#endif // CREATEGUILDFS_HPP