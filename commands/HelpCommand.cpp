#include "HelpCommand.hpp"

void HelpCommand::execute(std::optional<std::string> argument)
{
    Logger::log("\nUsage: guild [command] [options]\n"
                "Commands:\n"
                "  init [name]   Initialize a new project\n"
                "  help          Display help information\n");
}