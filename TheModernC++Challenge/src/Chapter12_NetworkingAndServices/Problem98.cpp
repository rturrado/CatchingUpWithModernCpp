#include "Chapter12_NetworkingAndServices.h"

#include "RtcConsoleRead.h"
#include "RtcPrint.h"

#include <algorithm>  // transform
#include <boost/algorithm/string.hpp>
#include <format>
#include <iostream>  // cout
#include <iterator>  // back_inserter
#include <optional>
#include <regex>  // regex_match, smatch, sregex_iterator
#include <sstream>  // istringstream, ostringstream
#include <string>  // getline, stoull
#include <string_view>
#include <unordered_map>
#include <vector>

#include "curlcpp/master/include/curl_easy.h"


enum class email_server_provider_t { gmail, hotmail, yahoo };


class ImapConnection
{
private:
    static inline const std::unordered_map<email_server_provider_t, std::string_view> email_server_provider_to_url{
        { email_server_provider_t::gmail, "imaps://imap.gmail.com" },
        { email_server_provider_t::hotmail, "imaps://imap-mail.outlook.com" },
        { email_server_provider_t::yahoo, "imaps://imap.mail.yahoo.com" }
    };
    static inline const size_t email_server_port{ 993 };

    void setup_easy(curl::curl_easy& easy) const
    {
        easy.add<CURLOPT_PORT>(email_server_port);
        easy.add<CURLOPT_USERNAME>(username_.c_str());
        easy.add<CURLOPT_PASSWORD>(password_.c_str());
        easy.add<CURLOPT_USE_SSL>(CURLUSESSL_ALL);
        easy.add<CURLOPT_SSL_VERIFYPEER>(0L);
        easy.add<CURLOPT_SSL_VERIFYHOST>(0L);
        easy.add<CURLOPT_USERAGENT>("libcurl-agent/1.0");
    }

    [[nodiscard]] auto parse_get_mailbox_folders_response(const std::string& response) const
    {
        std::vector<std::string> ret{};
        std::istringstream iss{ response };
        std::string line{};
        std::smatch matches{};
        const std::regex pattern{ R"(\* LIST \([^\)]+\) \"[^"]+\" \"([^\\]+)\".*)" };
        while (std::getline(iss, line))
        {
            boost::algorithm::trim_right(line);
            if (std::regex_match(line, matches, pattern))
            {
                ret.push_back(matches[1]);
            }
        }
        return ret;
    }

    [[nodiscard]] auto parse_get_unread_email_ids_response(std::string response) const
    {
        std::vector<std::size_t> ret{};
        std::smatch matches{};
        boost::algorithm::trim_right(response);
        const std::regex response_pattern{ R"(\* SEARCH(?: \d+)+)" };
        if (std::regex_match(response, matches, response_pattern))
        {
            const std::regex id_pattern{ R"(\d+)" };
            std::transform(
                std::sregex_iterator{ std::cbegin(response), std::cend(response), id_pattern },
                std::sregex_iterator{},
                std::back_inserter(ret),
                [](const std::smatch match) { return static_cast<size_t>(std::stoull(match.str())); }
            );
        }
        return ret;
    }

    [[nodiscard]] auto parse_email_subject(const std::string& email) const
    {
        std::optional<std::string> ret{};
        std::istringstream iss{ email };
        std::string line{};
        std::smatch matches{};
        const std::regex pattern{ R"(^Subject: .*$)" };
        while (std::getline(iss, line))
        {
            boost::algorithm::trim_right(line);
            if (std::regex_match(line, matches, pattern))
            {
                ret = matches[0].str();
                break;
            }
        }
        return ret;
    }

public:
    ImapConnection(email_server_provider_t provider, std::string_view username, std::string_view password)
        : provider_{ provider }
        , url_{ email_server_provider_to_url.at(provider_) }
        , username_{ username }
        , password_{ password }
    {}

    [[nodiscard]] auto get_mailbox_folders() const
    {
        std::optional<std::vector<std::string>> ret{};
        try
        {
            std::ostringstream oss{};
            curl::curl_ios<std::ostringstream> writer{ oss };
            curl::curl_easy easy{ writer };

            setup_easy(easy);
            easy.add<CURLOPT_URL>(url_.c_str());
            easy.perform();

            ret = parse_get_mailbox_folders_response(oss.str());
        }
        catch (const curl::curl_easy_exception& ex) {
            std::cout << "\tError: " << ex.what() << "\n";
        }
        return ret;
    }

    [[nodiscard]] auto get_unread_email_ids(std::string_view folder) const
    {
        std::optional<std::vector<size_t>> ret{};
        try
        {
            std::ostringstream oss{};
            curl::curl_ios<std::ostringstream> writer{ oss };
            curl::curl_easy easy{ writer };

            setup_easy(easy);
            std::ostringstream url_oss{};
            url_oss << url_ << "/" << folder.data() << "/";
            easy.add<CURLOPT_URL>(url_oss.str().c_str());
            easy.add<CURLOPT_CUSTOMREQUEST>("SEARCH UNSEEN");

            easy.perform();

            ret = parse_get_unread_email_ids_response(oss.str());
        }
        catch (const curl::curl_easy_exception& ex) {
            std::cout << "\tError: " << ex.what() << "\n";
        }
        return ret;
    }

    [[nodiscard]] auto get_email(std::string_view folder, size_t id) const
    {
        std::optional<std::string> ret{};
        try
        {
            std::ostringstream oss{};
            curl::curl_ios<std::ostringstream> writer{ oss };
            curl::curl_easy easy{ writer };

            setup_easy(easy);
            std::ostringstream url_oss{};
            url_oss << url_ << "/" << folder.data() << "/;UID=" << id;
            easy.add<CURLOPT_URL>(url_oss.str().c_str());

            easy.perform();

            ret = oss.str();
        }
        catch (const curl::curl_easy_exception& ex) {
            std::cout << "\tError: " << ex.what() << "\n";
        }
        return ret;
    }

    [[nodiscard]] auto get_email_subject(std::string_view folder, size_t id) const
    {
        std::optional<std::string> ret{};
        auto email_opt{ get_email(folder, id) };
        if (email_opt.has_value()) {
            ret = parse_email_subject(email_opt.value());
        }
        return ret;
    }

private:
    email_server_provider_t provider_{};
    std::string url_{};
    std::string username_{};
    std::string password_{};
};


// Fetching emails using IMAP
//
// Write a program that can get information from an email server using IMAP.
// The program should be able to:
//   - Get a list of folders from the mailbox.
//   - Get unread emails from a particular folder.
//
// Note: I tested this:
//   - with my gmail account,
//   - getting a third-party application password, and using it as a password, and
//   - marking some emails as unread in the doctorado folder (for some reason, I couldn't retrieve unread emails from the INBOX folder).
void problem_98_main()
{
    auto provider{ []() {
        auto input{ read_positive_number("Please enter your email service provider (0 for gmail, 1 for hotmail, 2 for yahoo): ", 0, 3) };
        return static_cast<email_server_provider_t>(input);
    }() };
    auto username{ []() {
        std::string ret{};
        std::cout << "Please enter your username: ";
        std::getline(std::cin, ret);
        return ret;
    }() };
    auto password{ []() {
        std::string ret{};
        std::cout << "Please enter your email password: ";
        std::getline(std::cin, ret);
        return ret;
    }() };

    auto imap_connection{ ImapConnection(provider, username, password) };

    std::cout << "List of folders from the mailbox:\n";
    auto folders_opt{ imap_connection.get_mailbox_folders() };
    if (folders_opt.has_value())
    {
        auto folders{ folders_opt.value() };
        if (not folders.empty())
        {
            for (auto& folder : folders) {
                std::cout << "\t" << folder << "\n";
            }

            auto folder{ []() {
                std::string ret{};
                std::cout << "Please enter a folder name: ";
                std::getline(std::cin, ret);
                return ret;
            }() };

            std::cout << std::format("List of unread emails from folder '{}':\n", folder);
            auto unread_email_ids_opt{ imap_connection.get_unread_email_ids(folder) };
            if (unread_email_ids_opt.has_value())
            {
                auto unread_email_ids{ unread_email_ids_opt.value() };
                if (not unread_email_ids.empty())
                {
                    for (auto&& id : unread_email_ids)
                    {
                        auto email_subject_opt{ imap_connection.get_email_subject(folder, id) };
                        if (email_subject_opt.has_value())
                        {
                            std::cout << "\t" << email_subject_opt.value() << "\n";
                        }
                    }
                } else {
                    std::cout << "\tThere are no unread emails\n";
                }
            }
        } else {
            std::cout << "\tThere are no folders in the mailbox\n";
        }
    }

    std::cout << "\n";
}
