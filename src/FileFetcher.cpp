#include "FileFetcher.h"

FileFetcher::FileFetcher(const std::string &url) : url_(url) {}

std::pair<std::string, std::string> FileFetcher::parseUrl(const std::string &url)
{
    std::regex urlRegex("^(https?://)?([^/]+)(/.*)?$");
    std::smatch matches;

    if (std::regex_match(url, matches, urlRegex))
    {
        std::string host = matches[2].str();
        std::string path = matches[3].length() > 0 ? matches[3].str() : "/";
        return {host, path};
    }
    return {"", ""};
}

std::optional<std::string> FileFetcher::fetchFileContent()
{
    auto [host, path] = parseUrl(url_);
    if (host.empty())
    {
        Logger::error("Invalid URL format");
        return std::nullopt;
    }

    bool isHttps = url_.substr(0, 8) == "https://";

    if (isHttps)
    {
        httplib::SSLClient cli(host);
        cli.set_follow_location(true);
        auto res = cli.Get(path.c_str());

        if (!res)
        {
            Logger::error("Failed to make a request to the server.");
            return std::nullopt;
        }

        if (res->status != 200)
        {
            Logger::error("Non-200 status code received: " + std::to_string(res->status));
            return std::nullopt;
        }

        Logger::info("File content fetched successfully.");
        return res->body;
    }
    else
    {
        httplib::Client cli(host);
        cli.set_follow_location(true);
        auto res = cli.Get(path.c_str());

        if (!res)
        {
            Logger::error("Failed to make a request to the server.");
            return std::nullopt;
        }

        if (res->status != 200)
        {
            Logger::error("Non-200 status code received: " + std::to_string(res->status));
            return std::nullopt;
        }

        Logger::info("File content fetched successfully.");
        return res->body;
    }
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

bool FileFetcher::fetchAndSave(const std::string &packageFolderPath)
{
    auto content = fetchFileContent();
    if (!content)
    {
        Logger::error("Failed to fetch content from the URL.");
        return false;
    }
    const std::string filePath = packageFolderPath + "testfile";
    if (!writeToFile(*content, filePath))
    {
        Logger::error("Failed to write content to the specified file.");
        return false;
    }
    Logger::info("File fetched and saved successfully.");
    return true;
}