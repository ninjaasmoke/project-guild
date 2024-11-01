#include "InitCommand.hpp"
#include "Logger.hpp" // Include necessary headers

InitCommand::InitCommand(const std::string &projectName) : projectName(projectName) {}

void InitCommand::execute()
{
    createGuildStructure(projectName);
    if (projectName.empty())
    {
        projectName = getCurrentFolder();
    }
    Logger::info("Guild created for project: " + projectName);
}
