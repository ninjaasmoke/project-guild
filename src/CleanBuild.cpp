#include "CleanBuild.hpp"

void cleanBuild()
{
    // for now we just do a clean build

    // get project name form `guild.json`
    std::ifstream file("./guild.json");

    if (!file.is_open())
    {
        Logger::error("Error: No guild.json file found in the current directory!");
        return;
    }

    json j;

    file >> j;

    std::string projectName = j["project_name"];

    // clean build

    // we only use GCC for now
    // include all files in the `src` folder. these files have headers in the `include` folder

    // first check if there are any files in the `src` folder

    fs::path srcPath = fs::current_path() / "src";

    if (!fs::exists(srcPath))
    {
        Logger::error("No `src` folder found in the current directory");
        return;
    }

    std::vector<std::string> files;
    std::string command;

    for (const auto &entry : fs::directory_iterator(srcPath))
    {
        files.push_back(entry.path().string());
    }

    if (files.empty())
    {
        // skip building the files in the `src` folder
        command = "g++ -std=c++17 -Iinclude main.cpp -o .bin/main -mconsole";
    }
    else
    {
        // command = "g++ -std=c++17 -Iinclude src/*.cpp main.cpp -o .bin/main -mconsole";
        command = "g++ -std=c++17 -Iinclude src/*.cpp src/*.c main.cpp -o .bin/main -mconsole";
    }

    Logger::log("Building project...");

    int result = std::system(command.c_str());

    if (result == 0)
    {
        Logger::info("Build successful");
    }
    else
    {
        Logger::error("Build failed");
    }

    // clean up
    file.close();

    return;
}