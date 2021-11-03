#include "Chapter6_AlgorithmsAndDataStructures.h"
#include "Print.h"

#include <algorithm>  // remove_if, transform
#include <functional>  // reference_wrapper
#include <iostream>  // cout
#include <regex>  // regex_match, regex_replace, smatch
#include <sstream>  // ostringstream
#include <string>
#include <vector>

using phone_numbers = std::vector<std::string>;

enum class country_code {
    US = 1,
    Spain = 34,
    UK = 44
};

void format_phone_numbers(phone_numbers& ph_nos, const country_code& cc)
{
    std::transform(begin(ph_nos), end(ph_nos), begin(ph_nos), [&cc](auto& ph_no) {
        // Remove whitespaces
        std::regex space_pattern{ R"([[:space:]])" };
        ph_no = std::regex_replace(ph_no, space_pattern, "");

        // Match a phone number. It can be of the form:
        // - +, country code, 10-digit number
        // - country code, 10-digit number
        // - 0, and then a 10-digit number
        // - 10 digit number
        // Country codes and 10-digit numbers shouldn't start with 0
        std::regex ph_no_pattern{R"((?:0?|([1-9][0-9]*)|\+([1-9][0-9]*))([1-9][0-9]{9}))"};
        std::smatch matches{};
        std::ostringstream oss{};
        if (std::regex_match(ph_no, matches, ph_no_pattern) and
            ((not matches[1].matched and not matches[2].matched) or
             (matches[1].matched and stoi(matches[1]) == static_cast<int>(cc)) or
             (matches[2].matched and stoi(matches[2]) == static_cast<int>(cc))))
        {
            oss << "+" << static_cast<int>(cc) << matches[3];  // outputs +, country code, 10-digit number
        }

        // Returns whether a formatted phone number or an empty string
        return oss.str();
    });

    // Removes empty strings from the list of phone numbers
    ph_nos.erase(std::remove_if(begin(ph_nos), end(ph_nos), [](const auto& ph_no) { return ph_no.empty(); }), end(ph_nos));
}

// Transforming a list of phone numbers
//
// Write a function that, given a list of phone numbers, transforms them so they all start with a specified country code,
// preceded by the + sign.
// Any whitespaces from a phone number should be removed.
// The following is a list of input and output examples:
//
// 07555 123456    => +447555123456
// 07555123456     => +447555123456
// +44 7555 123456 => +447555123456
// 44 7555 123456  => +447555123456
// 7555 123456     => +447555123456
void problem_51_main()
{
    phone_numbers good_cases{
        "07555 111111",
        "07555222222",
        "+44 7555 333333",
        "44 7555 444444",
        "7555 555555"
    };
    phone_numbers bad_cases{
        "+1 2345 666666",  // correct format, but wrong country code
        "34 987 7777777",  // same as above
        "0 12345678",  // doesn't contain a 10-digit number
        "+02 1234567890"  // country code starts with 0
    };

    for (auto& ph_nos : std::vector<std::reference_wrapper<phone_numbers>>{ good_cases, bad_cases })
    {
        std::cout << "List of phone numbers:\n\t" << ph_nos.get() << "\n";
        format_phone_numbers(ph_nos.get(), country_code::UK);
        std::cout << "List of UK phone numbers after formatting:\n\t" << ph_nos.get() << "\n\n";
    }
}
