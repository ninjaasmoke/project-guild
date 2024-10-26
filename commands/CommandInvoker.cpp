#include "CommandInvoker.hpp"
#include "InitCommand.hpp"
#include "HelpCommand.hpp"
#include "BuildCommand.hpp"
#include "RunCommand.hpp"
#include "Logger.hpp"

CommandInvoker::CommandInvoker()
{
    commands["init"] = std::make_unique<InitCommand>("");
    commands["help"] = std::make_unique<HelpCommand>();
    commands["build"] = std::make_unique<BuildCommand>();
    commands["run"] = std::make_unique<RunCommand>();
    commands["add"] = std::make_unique<RunCommand>();
}

void CommandInvoker::executeCommand(const std::string &command, const std::string &argument)
{
    if (commands.find(command) != commands.end())
    {
        if (!argument.empty())
        {
            Logger::info("Arguement: " + argument);
            // If argument is provided, update the corresponding command
            // commands[command] = std::make_unique<InitCommand>(argument);
        }
        commands[command]->execute();
    }
    else
    {
        Logger::error("Invalid command: " + command);
    }
}
