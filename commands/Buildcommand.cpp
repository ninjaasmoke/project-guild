#include "BuildCommand.hpp"

void BuildCommand::execute(std::optional<std::string> argument, std::optional<FlagMap> flags)
{
    cleanBuild();
}