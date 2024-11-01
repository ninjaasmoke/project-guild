// Flags.cpp
#include "Flags.h"

FlagMap parseFlags(int argc, char *argv[])
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
        // TODO: add single hyphen flag
    }

    return flags;
}