#include "RunCommand.hpp"

#ifdef __CYGWIN__
std::string command = "./.bin/main.exe"; // Unix-style path for Cygwin
#else
std::string command = ".bin\\main.exe"; // Windows-style path
#endif

void RunCommand::execute(std::optional<std::string> argument, std::optional<FlagMap> flags)
{

    std::ifstream file("./.bin/main.exe");

    if (!file.is_open())
    {
        Logger::error("Error: No  executable found! Have you tried `guild build`?");
        return;
    }

    Logger::log("Running project...");

    int result = std::system(command.c_str());

    if (result == 0)
    {
        Logger::info("Run successful!");
    }
    else
    {
        Logger::error("Run failed!");
    }

    return;
}