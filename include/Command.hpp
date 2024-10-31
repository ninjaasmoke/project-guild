#pragma once

#include "Logger.hpp"
#include "GetCurrentFolder.hpp"
#include "CreateGuildFS.hpp"
#include "CleanBuild.hpp"
#include "Flags.h"

#include <optional>

class Command
{
public:
    virtual void execute(std::optional<std::string> argument = std::nullopt, std::optional<FlagMap> flags = std::nullopt) = 0;
    virtual ~Command() = default;
};
