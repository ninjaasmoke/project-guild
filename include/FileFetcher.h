#ifndef FILEFETCHER_H
#define FILEFETCHER_H

#include "Logger.hpp"
#include "cpp-httplib/httplib.h"

#include <string>
#include <regex>
#include <fstream>
#include <cstdio>
#include <optional>

class FileFetcher
{
public:
    explicit FileFetcher(const std::string &url);

    // Public method to fetch and save the file
    bool fetchAndSave(const std::string &filePath);

    std::string getFilename() const;

private:
    std::string url_;

    // Private method to fetch content from the URL
    std::optional<std::string> fetchFileContent();

    // Private method to write content to a file
    bool writeToFile(const std::string &content, const std::string &filePath);

    // Private method to parseUrl
    std::pair<std::string, std::string> parseUrl(const std::string &url); // Corrected line
};

#endif // FILEFETCHER_H