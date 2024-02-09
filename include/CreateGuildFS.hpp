#include <string>
#include <filesystem>
#include <fstream>

#include "nlohmann/json.hpp"

void createGuildStructure(const std::string &projectName);
void createRootFolder(const std::string& projectName);
void createSubfolders(const std::string& rootPath);
void createDepJson(const std::string& rootPath, const std::string& projectName);
void createMainCpp(const std::string& rootPath, const std::string& projectName);