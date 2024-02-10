#include <iostream>
#include <unordered_map>
#include <functional>

#include "include/GetCurrentFolder.hpp"
#include "include/CreateGuildFS.hpp"
#include "include/Logger.hpp"

class Command
{
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

class InitCommand : public Command
{
private:
    std::string projectName;

public:
    InitCommand(const std::string &projectName) : projectName(projectName) {}

    void execute() override
    {
        createGuildStructure(projectName);
        if (projectName.empty())
        {
            projectName = getCurrentFolder();
        }
        Logger::info("Guild created for project: " + projectName);
    }
};

class HelpCommand : public Command
{
public:
    void execute() override
    {
        Logger::log("\nUsage: guild [command] [options]\n"
                    "Commands:\n"
                    "  init [name]   Initialize a new project\n"
                    "  help          Display help information\n");
    }
};

class CommandInvoker
{
private:
    std::unordered_map<std::string, std::unique_ptr<Command>> commands;

public:
    CommandInvoker()
    {
        commands["init"] = std::make_unique<InitCommand>("");
        commands["help"] = std::make_unique<HelpCommand>();
    }

    void executeCommand(const std::string &command, const std::string &argument)
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
};

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
