#include "CppHeaderValidator.h"

#include <fstream>
#include <regex>
#include <iterator>

bool CppHeaderValidator::isCppHeaderFile(const std::string &content)
{
    int score = 0;

    // header guard pattern: typical in C++ headers
    if (std::regex_search(content, std::regex("#ifndef\\s+\\w+")) &&
        std::regex_search(content, std::regex("#define\\s+\\w+")) &&
        content.find("#endif") != std::string::npos)
    {
        score += 3;
    }

    // common C++ header content: includes, namespaces, classes, structs
    std::regex cppKeywords("(#include\\s+<.*?>|namespace\\s+\\w+|class\\s+\\w+|struct\\s+\\w+|template\\s*<.*>)");
    score += std::distance(
        std::sregex_iterator(content.begin(), content.end(), cppKeywords),
        std::sregex_iterator());

    return score >= 4; // high threshold to ensure it's a C++ header file
}

bool CppHeaderValidator::validateDownloadedFile(const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        Logger::error("Failed to open file for validation: " + filePath);
        return false;
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    return isCppHeaderFile(content);
}
