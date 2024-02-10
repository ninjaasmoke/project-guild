#pragma once

#include "Logger.hpp"
#include "GetCurrentFolder.hpp"
#include "CreateGuildFS.hpp"

class Command
{
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};
