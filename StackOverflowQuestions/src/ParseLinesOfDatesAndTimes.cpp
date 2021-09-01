#include <chrono>  // duration, from_stream, sys_tyme
#include <iostream>  // cout
#include <map>  // map
#include <utility>  // pair
#include <sstream>  // istringstream
#include <string>  // string

void parse_lines_of_dates_and_times_main()
{
    // File line
    const std::string line{ "Start: 2021-03-01 09:00:00, Stop: 2021-03-01 14:32:31" };

    // Map of elapsed times for each start date/stop date pair of strings
    std::map<std::pair<std::string, std::string>, double> times;

    // Read each date and time field into a couple of time points
    std::istringstream iss{ line };
    //std::chrono::sys_time<std::chrono::seconds> start_tp{};
    //std::chrono::sys_time<std::chrono::seconds> stop_tp{};
    //if (std::chrono::from_stream(iss, "Start: %F %T", start_tp) and
    //    std::chrono::from_stream(iss, ", Stop: %F %T", stop_tp))
    std::chrono::system_clock::time_point start_tp{};
    std::chrono::system_clock::time_point stop_tp{};
    if (iss >> std::chrono::parse(std::string{ "Start: %F %T" }, start_tp) and
        iss >> std::chrono::parse(std::string{ ", Stop: %F %T" }, stop_tp))
    {
        // Calculate elapse time in ms between the start and stop time points
        double elapsed_time_ms = std::chrono::duration<double, std::milli>(stop_tp - start_tp).count();

        // Read start and stop dates into a pair of strings
        auto date_strings{ std::make_pair(line.substr(7, 19), line.substr(34, 19)) };

        // Add results to the map
        times[date_strings] = elapsed_time_ms;
    }

    // Print the map
    for (const auto& [date_str, time] : times)
    {
        std::cout << date_str.first << ", " << date_str.second << " = " << time << "\n";
    }
}
