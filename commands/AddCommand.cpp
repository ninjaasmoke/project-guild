#include "AddCommand.hpp"

void AddCommand::execute(std::optional<std::string> argument, std::optional<FlagMap> flags)
{

    if (!argument.has_value() || argument.value().size() == 0)
    {
        Logger::error("No argument found! Are you sure you are doing it right?");
        return;
    }

    // if (!flags.has_value())
    // {
    //     Logger::error("No flags provided! Are you sure you are doing it right?");
    //     return;
    // }

    // Logger::info("Hello" + argument.value());

    

    return;
}