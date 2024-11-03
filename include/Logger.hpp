#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>

class Logger
{
public:
    enum class LogLevel
    {
        INFO,
        WARNING,
        ERR
    };

    static void info(const std::string &message);
    static void warn(const std::string &message);
    static void error(const std::string &message);
    static void log(const std::string &message);

private:
    static void log(LogLevel level, const std::string &message);
    static void printColoredMessage(const std::string &message);
};

#endif // LOGGER_HPP
