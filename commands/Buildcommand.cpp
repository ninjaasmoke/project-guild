#include "BuildCommand.hpp"

void BuildCommand::execute(std::optional<std::string> argument)
{
    cleanBuild();
}