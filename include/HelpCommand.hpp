#pragma once
#include "Command.hpp"

class HelpCommand : public Command
{
public:
    void execute(std::optional<std::string> argument = std::nullopt, std::optional<FlagMap> flags = std::nullopt) override;
};