#ifndef FILEFETCHER_H
#define FILEFETCHER_H

#include "Logger.hpp"
#include "cpp-httplib/httplib.h"

#include <string>
#include <optional>

class FileFetcher
{
public:
    explicit FileFetcher(const std::string &url);

    // Public method to fetch and save the file
    bool fetchAndSave(const std::string &filePath);

private:
    std::string url_;

    // Private method to fetch content from the URL
    std::optional<std::string> fetchFileContent();

    // Private method to write content to a file
    bool writeToFile(const std::string &content, const std::string &filePath);
};

#endif // FILEFETCHER_H
