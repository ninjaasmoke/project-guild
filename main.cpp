#include <iostream>
#include <unordered_map>
#include <functional>

#include "include/GetCurrentFolder.hpp"
#include "include/CreateGuildFS.hpp"
#include "include/Logger.hpp"
#include "commands/Command.hpp"
#include "commands/CommandInvoker.hpp"

int main(int argc, char *argv[])
{
    CommandInvoker commandInvoker;

    if (argc >= 2)
    {
        std::string command = argv[1];
        std::string argument = (argc == 3) ? argv[2] : "";

        commandInvoker.executeCommand(command, argument);
    }
    else
    {
        Logger::error("Usage: " + std::string(argv[0]) + " [command] [options]");
        commandInvoker.executeCommand("help", "");
    }

    return 0;
}
