#pragma once

#include "Command.hpp"
#include "Flags.h"

#include <unordered_map>
#include <memory>

class CommandInvoker
{
private:
    std::unordered_map<std::string, std::unique_ptr<Command>> commands;

public:
    CommandInvoker();

    void executeCommand(const std::string &command, const std::string &argument, const FlagMap &flags);
};