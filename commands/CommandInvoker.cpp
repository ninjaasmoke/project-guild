#include "CommandInvoker.hpp"
#include "InitCommand.hpp"
#include "HelpCommand.hpp"
#include "Logger.hpp"

CommandInvoker::CommandInvoker()
{
    commands["init"] = std::make_unique<InitCommand>("");
    commands["help"] = std::make_unique<HelpCommand>();
}

void CommandInvoker::executeCommand(const std::string &command, const std::string &argument)
{
    if (commands.find(command) != commands.end())
    {
        if (!argument.empty())
        {
            // If argument is provided, update the corresponding command
            commands[command] = std::make_unique<InitCommand>(argument);
        }
        commands[command]->execute();
    }
    else
    {
        Logger::error("Invalid command: " + command);
    }
}
