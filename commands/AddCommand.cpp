#include "AddCommand.hpp"

void AddCommand::execute(std::optional<std::string> argument, std::optional<FlagMap> flags)
{
    if (!argument.has_value() || argument.value().empty())
    {
        Logger::error("No argument found! Are you sure you are doing it right?\n");
        Logger::good("Correct usage:\n\tguild add [resource]\n");
        return;
    }

    const std::string url = argument.value();
    if (!utils::url::isValidHttpUrl(url))
    {
        Logger::error(url + "\tis an invalid URL!");
        return;
    }

    // Ensure the packages directory exists
    std::string packageFolderPath = fs::current_path().string() + "/packages";
    if (!fs::exists(packageFolderPath))
    {
        fs::create_directories(packageFolderPath);
    }

    FileFetcher fileFetcher(url);
    if (!fileFetcher.fetchAndSave(packageFolderPath))
    {
        Logger::error("Failed to add resource!");
        return;
    }

    Logger::good("Added resource to '/packages' successfully!");
}