#include <chrono>
#include <iomanip>  // boolalpha
#include <iostream>  // cout
#include <sstream>  // istringstream
#include <string>

auto parse_string_to_duration(const std::string& str)
{
    std::istringstream iss{ str };
    // When there is no date information, you can't form a time_point
    // But you can form a duration which you can interpret as "time since midnight",
    // where you get to define midnight yourself
    std::chrono::microseconds d{};
    std::chrono::from_stream(iss, "%T", d);
    return d;
}

void parse_time_strings_to_durations_and_compare_main()
{
    const std::string str1{ "12:27:37.740002" };
    const std::string str2{ "23:39:48.500000" };

    auto d1{ parse_string_to_duration(str1) };
    auto d2{ parse_string_to_duration(str2) };

    std::cout << "d1 < d2: " << std::boolalpha << (d1 < d2) << "\n";
    std::cout << "d2 < d1: " << std::boolalpha << (d2 < d1) << "\n";
}
