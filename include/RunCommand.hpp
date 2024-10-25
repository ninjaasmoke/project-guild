#pragma once

#include "Command.hpp"

#include <filesystem>
#include <fstream>
#include <cstdlib>

class RunCommand : public Command
{
public:
    void execute() override;
};