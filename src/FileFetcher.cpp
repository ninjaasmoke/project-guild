// #include "cpp-httplib/httplib.h"
#include "FileFetcher.h"
#include <fstream>
#include <cstdio>

FileFetcher::FileFetcher(const std::string &url) : url_(url) {}

bool FileFetcher::fetchAndSave(const std::string &filePath)
{
    auto content = fetchFileContent();
    if (!content)
    {
        Logger::error("Failed to fetch content from the URL.");
        return false;
    }

    if (!writeToFile(*content, filePath))
    {
        Logger::error("Failed to write content to the specified file.");
        return false;
    }

    Logger::info("File fetched and saved successfully.");
    return true;
}

std::optional<std::string> FileFetcher::fetchFileContent()
{
    // httplib::Client cli(url_.c_str());
    // cli.set_follow_location(true);

    // auto res = cli.Get("/");
    // if (!res)
    // {
    //     Logger::error("Failed to make a request to the server.");
    //     return std::nullopt;
    // }

    // if (res->status != 200)
    // {
    //     Logger::error("Non-200 status code received: " + std::to_string(res->status));
    //     return std::nullopt;
    // }

    // Logger::info("File content fetched successfully.");
    // return res->body;

    return "";
}

bool FileFetcher::writeToFile(const std::string &content, const std::string &filePath)
{
    std::ofstream outfile(filePath, std::ios::binary);
    if (!outfile.is_open())
    {
        Logger::error("Failed to open file: " + filePath);
        return false;
    }

    outfile << content;
    if (!outfile)
    {
        Logger::error("Error writing content to file: " + filePath);
        return false;
    }

    outfile.close();
    if (outfile.fail())
    {
        Logger::error("Failed to close file after writing: " + filePath);
        return false;
    }

    Logger::info("Content written to file successfully.");
    return true;
}
