#include "Logger.hpp"

void Logger::info(const std::string &message)
{
    log(LogLevel::INFO, message);
}

void Logger::warn(const std::string &message)
{
    log(LogLevel::WARNING, message);
}

void Logger::good(const std::string &message)
{
    log(LogLevel::GOOD, message);
}

void Logger::error(const std::string &message)
{
    log(LogLevel::ERR, message);
}

void Logger::log(const std::string &message)
{
    std::cout << message << std::endl;
}

void Logger::log(LogLevel level, const std::string &message)
{
    switch (level)
    {
    case LogLevel::INFO:
        printColoredMessage("\033[1;36m" + message + "\033[0m"); // Cyan
        break;
    case LogLevel::WARNING:
        printColoredMessage("\033[1;33m" + message + "\033[0m"); // Yellow
        break;
    case LogLevel::ERR:
        printColoredMessage("\033[1;31m" + message + "\033[0m"); // Red
        break;
    case LogLevel::GOOD:
        printColoredMessage("\033[0;32m" + message + "\033[0m"); // Dark Green
        break;
    default:
        std::cout << message << std::endl;
    }
}

void Logger::printColoredMessage(const std::string &message)
{
    std::cout << message << std::endl;
}
