#include "GetCurrentFolder.hpp"

std::string getCurrentFolder()
{
    return std::filesystem::current_path().filename().string();
}