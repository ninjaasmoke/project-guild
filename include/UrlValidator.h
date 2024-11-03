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
            // Check if string is empty
            if (url.empty())
            {
                return false;
            }

            // Regular expression for HTTP/HTTPS URL validation
            static const std::regex urlPattern(
                R"(^(http|https):\/\/"  // Protocol
        "([a-zA-Z0-9]([a-zA-Z0-9\-]{0,61}[a-zA-Z0-9])?\.)+[a-zA-Z]{2,63}"  // Domain name
        "(:[0-9]{1,5})?"        // Optional port
        "(\/[a-zA-Z0-9\-._~:/?#\[\]@!$&'()*+,;=]*)?"  // Optional path and query
        "$)",
                std::regex::icase);

            try
            {
                // Attempt to match the URL against the pattern
                return std::regex_match(url, urlPattern);
            }
            catch (const std::regex_error &e)
            {
                // Handle any regex matching errors
                return false;
            }
        }

    } // namespace url
} // namespace utils

#endif // HTTP_URL_VALIDATOR_H