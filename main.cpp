#include <unordered_map>
#include <functional>

#include "include/GetCurrentFolder.hpp"
#include "include/CreateGuildFS.hpp"
#include "include/Logger.hpp"

#include "include/CommandInvoker.hpp"
#include "include/Command.hpp"
#include "include/Flags.h"

int main(int argc, char *argv[])
{
    CommandInvoker commandInvoker;

    const FlagMap flags = parseFlags(argc, argv);

    /*
        // Safer way to check for and use flags
        if (flags.count("--config")) {
            const auto& flag = flags["--config"];
            if (flag.hasValue) {
                // Use flag.value
            } else {
                Logger::error("--config requires a value");
                return 1;  // or handle error appropriately
            }
        }
    */

    if (argc >= 2)
    {
        std::string command = argv[1];
        std::string argument = (argc >= 3) ? argv[2] : "";

        // if (flags.find("--verbose") != flags.end())
        // {
        //     std::cout << "Verbose mode enabled" << std::endl;
        // }

        Logger::info("Executing: " + command);

        commandInvoker.executeCommand(command, argument, flags);
    }
    else
    {
        Logger::error("Usage: " + std::string(argv[0]) + " [command] [options]");
        commandInvoker.executeCommand("help", "", flags);
    }

    return 0;
}
