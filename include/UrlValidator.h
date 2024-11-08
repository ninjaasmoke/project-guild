#ifndef HTTP_URL_VALIDATOR_H
#define HTTP_URL_VALIDATOR_H

#include <string>
#include <regex>

namespace utils
{
    namespace url
    {

        /**
         * @brief Validates if a given string is a valid HTTP/HTTPS URL
         * @param url The string to validate
         * @return true if the string is a valid HTTP/HTTPS URL, false otherwise
         */
        inline bool isValidHttpUrl(const std::string &url)
        {
            if (url.empty())
            {
                return false;
            }

            const std::regex urlPattern(
                R"(^(http|https):\/\/([a-zA-Z0-9]([a-zA-Z0-9\-]{0,61}[a-zA-Z0-9])?\.)+[a-zA-Z]{2,63}(:[0-9]{1,5})?(\/[a-zA-Z0-9\-._~:/?#\[\]@!$&'()*+,;=]*)?$)",
                std::regex::icase);

            try
            {
                return std::regex_match(url, urlPattern);
            }
            catch (const std::regex_error &e)
            {
                return false;
            }
        }

    } // namespace url
} // namespace utils

#endif // HTTP_URL_VALIDATOR_H