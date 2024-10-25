#include <unordered_map>
#include <functional>

#include "include/GetCurrentFolder.hpp"
#include "include/CreateGuildFS.hpp"
#include "include/Logger.hpp"

#include "include/CommandInvoker.hpp"
#include "include/Command.hpp"

std::map<std::string, std::string> parseFlags(int argc, char *argv[])
{
    std::map<std::string, std::string> flags;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg.find("--") == 0)
        { // Long flag (e.g., --option)
            if (i + 1 < argc && !std::string(argv[i + 1]).find("-"))
            {
                flags[arg] = argv[i + 1]; // Associate flag with its value
                ++i;                      // Skip the next argument since it's the value
            }
            else
            {
                flags[arg] = ""; // Flag without a value
            }
        }
        else if (arg.find("-"))
        {                    // Short flag (e.g., -o)
            flags[arg] = ""; // You can extend this to handle short flags with values
        }
    }

    return flags;
}

int main(int argc, char *argv[])
{
    CommandInvoker commandInvoker;

    auto flags = parseFlags(argc, argv);

    if (argc >= 2)
    {
        std::string command = argv[1];
        std::string argument = (argc == 3) ? argv[2] : "";

        if (flags.find("--verbose") != flags.end())
        {
            std::cout << "Verbose mode enabled" << std::endl;
        }

        Logger::info("Executing: " + command);

        commandInvoker.executeCommand(command, argument);
    }
    else
    {
        Logger::error("Usage: " + std::string(argv[0]) + " [command] [options]");
        commandInvoker.executeCommand("help", "");
    }

    return 0;
}
