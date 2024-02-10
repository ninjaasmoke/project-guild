#include "CreateGuildFS.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

void createProjectStructure(const std::string &rootPath, const std::string &projectName)
{
    createRootFolder(rootPath);
    createSubfolders(rootPath);
    createDepJson(rootPath, projectName);
    createMainCpp(rootPath, projectName);
}

void createRootFolder(const std::string &rootPath)
{
    // Create the root folder
    std::filesystem::create_directory(rootPath);
}

void createSubfolders(const std::string &rootPath)
{
    // Create subfolders within the root folder
    for (const std::string &subfolder : {"dependencies", "include", ".build", "src", ".bin"})
    {
        std::filesystem::create_directory(rootPath + "/" + subfolder);
    }
}

void createDepJson(const std::string &rootPath, const std::string &projectName)
{
    // Initialize and populate guild.json
    json depJson;
    depJson["project_name"] = projectName;
    depJson["version"] = "1.0.0";
    depJson["comments"] = "hello darkness my old friend...";
    depJson["dependencies"] = json::array();
    json::array_t compile = json::array();
    compile.push_back("include");
    compile.push_back("src");
    depJson["compile"] = compile;

    std::ofstream depFile(rootPath + "/guild.json");
    depFile << std::setw(4) << depJson << std::endl;
    depFile.close();
}

void createMainCpp(const std::string &rootPath, const std::string &projectName)
{
    // Create and write content to main.cpp
    std::ofstream mainFile(rootPath + "/main.cpp");
    mainFile << "#include <iostream>\n\n";
    mainFile << "int main() {\n";
    mainFile << "  std::cout << \"Hello, " << projectName << "!\" << std::endl;\n";
    mainFile << "  return 0;\n";
    mainFile << "}\n";
    mainFile.close();
}

void createGuildStructure(const std::string &projectName)
{
    // If no project name is provided, use the current folder name
    if (projectName.empty())
    {
        std::string currentFolder = getCurrentFolder();
        createProjectStructure("./", currentFolder);
    }
    else
    {
        createProjectStructure(projectName, projectName);
    }
}
