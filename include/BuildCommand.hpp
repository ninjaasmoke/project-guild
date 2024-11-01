#pragma once

#include "Command.hpp"

#include <filesystem>

class BuildCommand : public Command
{
public:
    void execute(std::optional<std::string> argument = std::nullopt, std::optional<FlagMap> flags = std::nullopt) override;
};