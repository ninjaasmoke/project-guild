#include "CreateGuildFS.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

const std::string INCLUDE_DIR = "include";
const std::string SRC_DIR = "src";
const std::string HEADER_FILE = "myclass.hpp";
const std::string C_HEADER_FILE = "myfunctions.h";
const std::string CPP_FILE = "myclass.cpp";
const std::string C_FILE = "myfunctions.c";
const std::string MAIN_CPP_FILE = "main.cpp";

void createProjectStructure(const std::filesystem::path &rootPath, const std::string &projectName)
{
    if (!createRootFolder(rootPath))
    {
        std::cerr << "Failed to create root folder.\n";
        return;
    }

    if (!createSubfolders(rootPath))
    {
        std::cerr << "Failed to create subfolders.\n";
        return;
    }

    if (!createDepJson(rootPath, projectName))
    {
        std::cerr << "Failed to create dep.json.\n";
        return;
    }

    if (!createSampleHeaderFiles(rootPath))
    {
        std::cerr << "Failed to create sample header files.\n";
        return;
    }

    if (!createSampleSourceFiles(rootPath))
    {
        std::cerr << "Failed to create sample source files.\n";
        return;
    }

    if (!createMainCpp(rootPath, projectName))
    {
        std::cerr << "Failed to create main.cpp.\n";
        return;
    }

    std::cout << "Project " << projectName << " created successfully!\n";
}

bool createRootFolder(const std::filesystem::path &rootPath)
{
    try
    {
        // Check if path already exists
        if (std::filesystem::exists(rootPath))
        {
            if (std::filesystem::is_directory(rootPath))
            {
                std::cout << "Directory already exists: " << rootPath << '\n';
                return true;
            }
            else
            {
                throw std::runtime_error("Path exists but is not a directory: " + rootPath.string());
            }
        }

        // Create directory and all parent directories if needed
        if (std::filesystem::create_directories(rootPath))
        {
            std::cout << "Created directory: " << rootPath << '\n';
            return true;
        }
        else
        {
            throw std::runtime_error("Failed to create directory: " + rootPath.string());
        }
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::cerr << "Filesystem error: " << e.what() << '\n';
        return false;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
}

bool createSubfolders(const std::filesystem::path &rootPath)
{
    // Default folders to create
    const std::vector<std::string> defaultFolders = {
        "packages",
        "include",
        "resources",
        ".build",
        "src",
        ".bin"};

    try
    {
        // Ensure root path exists first
        std::filesystem::create_directories(rootPath);

        // Create each subfolder
        for (const auto &subfolder : defaultFolders)
        {
            auto folderPath = rootPath / subfolder;

            if (std::filesystem::exists(folderPath))
            {
                std::cout << "Folder already exists: " << folderPath << '\n';
                continue;
            }

            if (!std::filesystem::create_directory(folderPath))
            {
                throw std::runtime_error("Failed to create folder: " + folderPath.string());
            }

            std::cout << "Created folder: " << folderPath << '\n';
        }

        return true;
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::cerr << "Filesystem error: " << e.what() << '\n';
        return false;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
}

bool createDepJson(const std::filesystem::path &rootPath, const std::string &projectName)
{
    try
    {
        // Create and populate the JSON structure
        json depJson = {
            {"project_name", projectName},
            {"version", "1.0.0"},
            {"description", "Project configuration file"},
            {"author", ""},
            {"license", "MIT"},
            {"dependencies", json::array()},
            {"dev_dependencies", json::array()},
            {"compile", {"include", "src"}},
            {"build_settings", {{"output_dir", ".bin"}, {"intermediate_dir", ".build"}}},
            {"scripts", {{"build", ""}, {"test", ""}, {"clean", ""}}}};

        // Ensure directory exists
        std::filesystem::create_directories(rootPath);

        // Open file with error checking
        std::ofstream depFile(rootPath / "guild.json");
        if (!depFile)
        {
            throw std::runtime_error("Failed to create guild.json");
        }

        // Write JSON with proper formatting
        depFile << std::setw(4) << depJson << std::endl;

        return true;
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::cerr << "Filesystem error: " << e.what() << '\n';
        return false;
    }
    catch (const json::exception &e)
    {
        std::cerr << "JSON error: " << e.what() << '\n';
        return false;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
}

bool createSampleHeaderFiles(const std::filesystem::path &rootPath)
{
    try
    {
        // Ensure directory exists
        std::filesystem::create_directories(rootPath / INCLUDE_DIR);

        // Create file using proper path composition
        std::ofstream hppFile(rootPath / INCLUDE_DIR / HEADER_FILE);
        if (!hppFile)
        {
            throw std::runtime_error("Failed to create C++ header file");
        }

        const char *headerContent = R"(/*
This is a sample file.
You can delete this file.
*/

// myclass.hpp

#ifndef MYCLASS_HPP
#define MYCLASS_HPP

class MyClass {
public:
    void printMessage();
};

#endif)";

        hppFile << headerContent;

        std::ofstream hFile(rootPath / INCLUDE_DIR / C_HEADER_FILE);

        if (!hFile)
        {
            throw std::runtime_error("Failed to create C header file");
        }

        headerContent = R"(/*
This is a sample file.
You can delete this file.
*/

// myfunctions.h

#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

void cFunction();

#ifdef __cplusplus
}
#endif

#endif)";

        hFile << headerContent;

        return true;
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::cerr << "Filesystem error: " << e.what() << '\n';
        return false;
    }
    catch (const json::exception &e)
    {
        std::cerr << "JSON error: " << e.what() << '\n';
        return false;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
}

bool createSampleSourceFiles(const std::filesystem::path &rootPath)
{
    try
    {
        std::filesystem::create_directories(rootPath / SRC_DIR);

        std::ofstream cppFile(rootPath / SRC_DIR / CPP_FILE);

        if (!cppFile)
        {
            throw std::runtime_error("Failed to create source C++ file");
        }

        const char *sourceFileContent = R"(/*
This is a sample file.
You can delete this file.
*/

// myclass.cpp

#include "myclass.hpp"
#include <iostream>

void MyClass::printMessage() {
    std::cout << "Hello from MyClass!" << std::endl;
})";

        cppFile << sourceFileContent;

        std::ofstream cFile(rootPath / SRC_DIR / C_FILE);

        if (!cFile)
        {
            throw std::runtime_error("Failed to create source C file");
        }

        sourceFileContent = R"(/*
This is a sample file.
You can delete this file.
*/

// myfunctions.c

#include "myfunctions.h"
#include <stdio.h>

void cFunction() {
    printf("Hello from C function!\n");
})";

        cFile << sourceFileContent;

        return true;
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::cerr << "Filesystem error: " << e.what() << '\n';
        return false;
    }
    catch (const json::exception &e)
    {
        std::cerr << "JSON error: " << e.what() << '\n';
        return false;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
}

bool createMainCpp(const std::filesystem::path &rootPath, const std::string &projectName)
{
    try
    {
        // Ensure the directory exists
        std::filesystem::create_directories(rootPath);

        // Prepare the main.cpp content
        std::ostringstream mainContent;
        mainContent << R"(// main.cpp
#include "myclass.hpp"
#include "myfunctions.h"

int main() {
    MyClass myClassObj;
    myClassObj.printMessage();
    
    cFunction();
    
    return 0;
}
)";

        // Create the file with error checking
        auto mainPath = rootPath / MAIN_CPP_FILE;
        std::filesystem::create_directories(mainPath.parent_path());

        std::ofstream mainFile(mainPath);
        if (!mainFile)
        {
            throw std::runtime_error("Failed to create main.cpp");
        }

        mainFile << mainContent.str();

        return true;
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::cerr << "Filesystem error: " << e.what() << '\n';
        return false;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
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
