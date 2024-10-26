#include <unordered_map>
#include <functional>

#include "include/GetCurrentFolder.hpp"
#include "include/CreateGuildFS.hpp"
#include "include/Logger.hpp"

#include "include/CommandInvoker.hpp"
#include "include/Command.hpp"

struct Flag
{
    std::string name;
    std::string value;
    bool hasValue; // Explicitly track if flag has a value
};

std::map<std::string, Flag> parseFlags(int argc, char *argv[])
{
    std::map<std::string, Flag> flags;

    // Skip program name (argv[0])
    for (int i = 1; i < argc; ++i)
    {
        // Prevent buffer overruns by checking string validity
        if (!argv[i])
            continue;

        std::string arg = argv[i];
        if (arg.empty())
            continue;

        if (arg.find("--") == 0)
        { // Long flag
            std::string flagName = arg;
            std::string value;
            bool hasValue = false;

            // Check if next argument exists and is a value (not a flag)
            if (i + 1 < argc && argv[i + 1] && argv[i + 1][0] != '-')
            {
                value = argv[i + 1];
                hasValue = true;
                ++i; // Skip the value in next iteration
            }

            flags[flagName] = Flag{flagName, value, hasValue};
        }
    }

    return flags;
}

int main(int argc, char *argv[])
{
    CommandInvoker commandInvoker;

    auto flags = parseFlags(argc, argv);

    for (const auto &[name, flag] : flags)
    {
        if (flag.hasValue)
        {
            Logger::info("Flag: " + name + " = " + flag.value);
        }
        else
        {
            Logger::info("Flag: " + name + " (no value)");
        }
    }

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
