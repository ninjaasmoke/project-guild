#ifndef CREATEGUILDFS_HPP
#define CREATEGUILDFS_HPP

#include <string>
#include <filesystem>
#include <fstream>

#include "GetCurrentFolder.hpp"
#include "nlohmann/json.hpp"

void createGuildStructure(const std::string &projectName);
void createRootFolder(const std::string& projectName);
void createSubfolders(const std::string& rootPath);
void createDepJson(const std::string& rootPath, const std::string& projectName);
void createMainCpp(const std::string& rootPath, const std::string& projectName);

#endif // CREATEGUILDFS_HPP