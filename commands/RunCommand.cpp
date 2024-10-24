#include "RunCommand.hpp"

void RunCommand::execute()
{

    std::ifstream file("./.bin/main.exe");

    if (!file.is_open())
    {
        Logger::error("Error: No  executable found! Have you tried `guild build`?");
        return;
    }

    std::string command = ".bin\\main.exe";  // Use Windows path format :: TODO: system agnostic

    Logger::log("Running project...");

    int result = std::system(command.c_str());

    if (result == 0)
    {
        Logger::log("Run successful!");
    }
    else
    {
        Logger::error("Run failed!");
    }

    return;
}