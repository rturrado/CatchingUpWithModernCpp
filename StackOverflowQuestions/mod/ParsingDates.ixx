export module ParsingDates;

import <chrono>;  // parse, sys_days, weekday
import <iostream>;  // cout
import <regex>;  // regex_match, smatch
import <sstream>;  // istringstream

namespace ch = std::chrono;

void using_just_chrono(const std::string& date)
{
    ch::year_month_day ymd{};
    std::istringstream iss{ date };
    if (iss >> ch::parse(std::string{ "%Y/%m/%d" }, ymd) and ymd.ok())
    {
        std::cout << "\t\tusing just chrono: " << ch::weekday{ ch::sys_days{ ymd } } << "\n";
    }
}

void using_regex_and_chrono(const std::string& date)
{
    std::regex pattern{ R"(^[[:space:]]*([[:digit:]]{1,4})/([[:digit:]]{1,2})/([[:digit:]]{1,2})[[:space:]]*$)" };
    std::smatch matches{};
    if (std::regex_match(date, matches, pattern))
    {
        ch::year_month_day ymd(
            ch::year{ std::stoi(matches[1]) },
            ch::month{ std::stoul(matches[2]) },
            ch::day{ std::stoul(matches[3]) });
        if (ymd.ok())
        {
            std::cout << "\t\tusing rgx and chr: " << ch::weekday{ ch::sys_days{ ymd } } << "\n";
        }
    }
}

export void parsing_dates_main()
{
    std::cout << "Parsing dates:\n";
    for (const std::string& date : {
        "2021/03/01",  // OK
        "  2022/4/2",  // OK: needs trimming white spaces at the front
        "5/3/2023",  // wrong: day is 2023
        "abracadabra",  // wrong format
        "2020/12/32",  // wrong: day is 32
        "2019/13/20",  // wrong: month is 13
        "2021/2/29" })  // wrong: non existing date
    {
        std::cout << "\t\"" << date << "\":\n";
        using_just_chrono(date);
        using_regex_and_chrono(date);
    }
    std::cout << "\n";
}

// Outputs:
//
// Parsing dates:
//     "2021/03/01":
//         using just chrono: Mon
//         using rgx and chr: Mon
//     "  2022/4/2":
//         using rgx and chr: Sat
//     "5/3/2023":
//         using just chrono: Sun
//     "abracadabra":
//     "2020/12/32":
//     "2019/13/20":
//     "2021/2/29":
