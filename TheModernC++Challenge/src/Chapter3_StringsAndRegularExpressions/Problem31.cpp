#include <exception>
#include <iomanip>  // setw
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

struct invalid_date_format : public std::exception
{
    explicit invalid_date_format(const std::string& date) noexcept { message_ += "\"" + date + "\""; }
    const char* what() const noexcept { return message_.c_str(); }
private:
    std::string message_{ "invalid date format: "};
};

std::string format_date_v1(const std::string& s)
{
    uint16_t year{ 0 };
    uint16_t month{ 0 };
    uint16_t day{ 0 };

    std::smatch matches{};
    const std::regex valid_format_pattern_1{ R"(([[:digit:]]{1,2})\.([[:digit:]]{1,2})\.([[:digit:]]{1,4}))" };
    const std::regex valid_format_pattern_2{ R"(([[:digit:]]{1,2})\-([[:digit:]]{1,2})\-([[:digit:]]{1,4}))" };
    if ((std::regex_match(s, matches, valid_format_pattern_1) or
        std::regex_match(s, matches, valid_format_pattern_2)) and
        matches.size() == 4)
    {
        day = stoi(matches[1].str());
        month = stoi(matches[2].str());
        year = stoi(matches[3].str());
    }
    else
    {
        throw invalid_date_format(s);
    }

    std::ostringstream oss{};
    oss << std::setfill('0') << std::setw(4) << year << "-" << std::setw(2) << month << "-" << std::setw(2) << day;
    return oss.str();
}

// Book's solution
//
// - Works directly on a string_view
// - Performs a regex match and then writes the matched fields, in different order, directly over the string_view's data
// - If the input string doesn't match the regex pattern, it is returned unmodified
//
// - It doesn't care about different separators being used in the same input date; it even considers '/' as a separator
// - It doesn't pad each output field with '0's either
std::string format_date_v2(std::string_view sv)
{
    const std::regex valid_format_pattern{ R"(([[:digit:]]{1,2})[\.|\-|/]([[:digit:]]{1,2})[\.|\-|/]([[:digit:]]{1,4}))" };
    const std::string new_format_pattern{ R"($3-$2-$1)" };
    return std::regex_replace(sv.data(), valid_format_pattern, new_format_pattern);
}

// Transforming dates in strings
//
// Write a function that, given a text containing dates in the format dd.mm.yyyy or dd-mm-yyyy,
// transforms the text so that it contains dates in the format yyyy-mm-dd
void problem_31_main()
{
    for (auto& date : { "1-1-1980", "25-12-0", "1-111-1980", "1.1-1980", "1/1/1980" })
    {
        std::cout << "Input string: " << date << "\n";
        try
        {
            std::cout << "\tBook's solution: " << format_date_v2(date) << "\n";
            std::cout << "\tMy solution: " << format_date_v1(date) << "\n";
        }
        catch (const std::exception& err)
        {
            std::cout << "Error: " << err.what() << "\n";
        }
    }

    std::cout << "\n";
}
