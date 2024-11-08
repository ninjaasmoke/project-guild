#ifndef CPPHEADERVALIDATOR_H
#define CPPHEADERVALIDATOR_H

#include "Logger.hpp"

#include <string>

class CppHeaderValidator
{
public:
    // validates if the content of a file at the given path is a C++ header file
    bool validateDownloadedFile(const std::string &filePath);

private:
    // checks if the content matches C++ header characteristics
    bool isCppHeaderFile(const std::string &content);
};

#endif // CPPHEADERVALIDATOR_H
