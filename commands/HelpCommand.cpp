#include "HelpCommand.hpp"

void HelpCommand::execute()
{
    Logger::log("\nUsage: guild [command] [options]\n"
                "Commands:\n"
                "  init [name]   Initialize a new project\n"
                "  help          Display help information\n");
}