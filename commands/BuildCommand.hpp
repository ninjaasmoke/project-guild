#pragma once

#include "Command.hpp"
#include "Logger.hpp"

#include <filesystem>

class BuildCommand : public Command
{
public:
    void execute() override;
};