#pragma once
#include "Command.hpp"

class HelpCommand : public Command
{
public:
    void execute() override;
};