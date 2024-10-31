#pragma once
#include "Command.hpp"

#include <string>

class InitCommand : public Command
{
private:
    std::string projectName;

public:
    InitCommand(const std::string &projectName);

    void execute(std::optional<std::string> argument = std::nullopt, std::optional<FlagMap> flags = std::nullopt) override;
};
