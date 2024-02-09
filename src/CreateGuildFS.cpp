#include "CreateGuildFS.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

void createGuildStructure(const std::string &projectName)
{
    // Define the root folder name
    std::string rootFolderName = projectName;

    // Create the root folder
    fs::create_directory(rootFolderName);

    // Create subfolders inside the root folder
    fs::create_directory(rootFolderName + "/dependencies");
    fs::create_directory(rootFolderName + "/include");
    fs::create_directory(rootFolderName + "/.build");
    fs::create_directory(rootFolderName + "/src");
    fs::create_directory(rootFolderName + "/.bin");

    // Create dep.guild.json file
    json depJson;
    depJson["project_name"] = projectName;
    depJson["version"] = "1.0.0";
    depJson["comments"] = "Add your comments here";
    depJson["dependencies"] = json::array();

    std::ofstream depFile(rootFolderName + "/dep.guild.json");
    depFile << std::setw(4) << depJson << std::endl;
    depFile.close();

    // Create main.cpp in the root folder
    std::ofstream mainFile(rootFolderName + "/main.cpp");
    mainFile << "#include <iostream>\n\n";
    mainFile << "int main() {\n";
    mainFile << "    std::cout << \"Hello, " << projectName << "!\" << std::endl;\n";
    mainFile << "    return 0;\n";
    mainFile << "}\n";
    mainFile.close();
}