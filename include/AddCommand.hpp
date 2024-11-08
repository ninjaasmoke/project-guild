#pragma once

#include "UrlValidator.h"
#include "Command.hpp"
#include "FileFetcher.h"

#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <string>

class AddCommand : public Command
{
public:
    void execute(std::optional<std::string> argument = std::nullopt, std::optional<FlagMap> flags = std::nullopt) override;
};