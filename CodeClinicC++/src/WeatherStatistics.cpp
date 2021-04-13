#include "WeatherStatistics.h"

#include <algorithm>
#include <array>
#include <filesystem>
#include <iostream>
#include <sstream>

using namespace std::filesystem;

std::time_t to_time_t(const std::string& date, const std::string& time)
{
    std::time_t ret{};
    std::tm tm{};

    std::string date_copy{ date };
    std::transform(date.begin(), date.end(), date_copy.begin(), [](const char& c) {return (c == '_' ? ' ' : c); });
    std::istringstream ss_date{ date_copy };
    ss_date >> tm.tm_year >> tm.tm_mon >> tm.tm_mday;
    tm.tm_year -= 1900;  // years since 1900
    tm.tm_mon -= 1;  // months since January


    std::string time_copy{ time };
    std::transform(time.begin(), time.end(), time_copy.begin(), [](const char& c) {return (c == ':' ? ' ' : c); });
    std::istringstream ss_time{ time_copy};
    ss_time >> tm.tm_hour >> tm.tm_min >> tm.tm_sec;

    ret = std::mktime(&tm);

    return ret;
}

std::string time_t_to_string(std::time_t time_point)
{
    struct std::tm time_info;
    localtime_s(&time_info, &time_point);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << time_info.tm_year + 1900 << '_' << std::setw(2) << time_info.tm_mon + 1 << '_' << std::setw(2) << time_info.tm_mday;
    oss << ' ';
    oss << std::setfill('0') << std::setw(2) << time_info.tm_hour << ':' << std::setw(2) << time_info.tm_min << ':' << std::setw(2) << time_info.tm_sec;

    return oss.str();
}

void WeatherData::read_data_files()
{
    const path data_folder{ "D:\\Programacion\\code\\c++\\code_clinic_c++\\Exercise Files\\CH01\\resources" };

    // Walk all files in a given folder
    if (is_directory(data_folder))
    {
        std::cout << "Reading data folder: " << data_folder << "\n";
        for (const directory_entry& x : directory_iterator{ data_folder })
        {
            std::cout << "Reading data file: " << x.path() << "\n";

            // Open file
            std::ifstream data_file_fs{ x };
            // Read header
            read_header(data_file_fs);
            // Read data
            read_data_file(data_file_fs);
            // Close file
            data_file_fs.close();
        }
    }
    else
    {
        throw DataFolderNotFoundException(data_folder.string() + " not found.");
    }
}

void WeatherData::read_header(std::ifstream& ifs)
{
    const std::array<std::string, 9> header_strings{
        "date", "time", "Air_Temp", "Barometric_Press", "Dew_Point", "Relative_Humidity", "Wind_Dir", "Wind_Gust", "Wind_Speed"
    };
    for (size_t i = 0; i < header_strings.size(); ++i)
    {
        std::string temp_str;
        ifs >> temp_str;
        if (temp_str != header_strings[i])
        {
            throw HeaderFormatException("parsing header: " + temp_str + " != " + header_strings[i]);
        }
    }
}

void WeatherData::read_data_file(std::ifstream& data_file_fs)
{
    while (!data_file_fs.eof())
    {
        WeatherDataEntry entry;
        std::string entry_date{};
        std::string entry_time{};
        data_file_fs
            >> entry_date
            >> entry_time
            >> entry.air_temperature
            >> entry.barometric_presure
            >> entry.dew_point
            >> entry.relative_humidity
            >> entry.wind_direction
            >> entry.wind_gust
            >> entry.wind_speed;
        std::time_t time_point = to_time_t(entry_date, entry_time);
        if (time_point != -1)
        {
            data_[time_point] = entry;
        }
    }
}

std::time_t WeatherData::get_first_time_point()
{
    auto first_weather_data_it{ data_.begin() };
    return first_weather_data_it->first;
}

std::time_t WeatherData::get_last_time_point()
{
    auto last_weather_data_it{ data_.rbegin() };
    return last_weather_data_it->first;
}

float WeatherData::calculate_barometric_pressure_slope_coefficient(const TimePointRange& time_point_range)
{
    // Get iterators to begin and end positions
    auto begin_it = data_.lower_bound(time_point_range.begin);
    auto end_it = data_.lower_bound(time_point_range.end);

    // Extract times and barometric_pressures
    float begin_pressure = begin_it->second.barometric_presure;
    float end_pressure = end_it->second.barometric_presure;
    std::time_t begin_time_point = begin_it->first;
    std::time_t end_time_point = end_it->first;

    // Calculate slope coefficient
    return (end_pressure - begin_pressure) / (end_time_point - begin_time_point);
}

bool is_valid_time_point(const std::string& date, const std::string& time, const TimePointRange& weather_data_time_range)
{
    std::time_t time_point = to_time_t(date, time);
    if (time_point == -1)
    {
        std::cout << "Sorry, the date and time are incorrect. Make sure the format is OK, the date is valid, and the year is above or equal 1900.\n";
        return false;
    }
    if (time_point < weather_data_time_range.begin)
    {
        std::cout << "First valid date is " << time_t_to_string(weather_data_time_range.begin) << ".\n";
        return false;
    }
    if (time_point > weather_data_time_range.end)
    {
        std::cout << "Last valid date is " << time_t_to_string(weather_data_time_range.end) << ".\n";
        return false;
    }
    return true;
}

TimePointRange read_date_range(const TimePointRange& weather_data_time_range)
{
    TimePointRange ret{};

    std::string begin_date{};
    std::string begin_time{};
    while (true)
    {
        std::cout << "Please input begin date (YYYY_MM_DD format): ";
        std::cin >> begin_date;
        std::cout << "Please input begin time (hh:mm:ss format): ";
        std::cin >> begin_time;
        if (is_valid_time_point(begin_date, begin_time, weather_data_time_range))
        {
            ret.begin = to_time_t(begin_date, begin_time);
            break;
        }
    }

    std::string end_date{};
    std::string end_time{};
    while (true)
    {
        std::cout << "Please input end date (YYYY_MM_DD format): ";
        std::cin >> end_date;
        std::cout << "Please input end time (hh:mm:ss 24 hour format): ";
        std::cin >> end_time;
        if (is_valid_time_point(end_date, end_time, weather_data_time_range))
        {
            ret.end = to_time_t(end_date, end_time);
            break;
        }
    }

    return ret;
}

void weather_statistics_main()
{
    try
    {
        // Read data files into a vector of data
        std::cout << "Reading data...\n";
        WeatherData weather_data{};

        // Read begin and end date and times
        TimePointRange weather_data_time_range{ weather_data.get_first_time_point(), weather_data.get_last_time_point() };
        TimePointRange user_time_range = read_date_range(weather_data_time_range);

        // Calculate barometric pressure slope
        float slope_coefficient = weather_data.calculate_barometric_pressure_slope_coefficient(user_time_range);
        std::cout << "Slope coefficient (inHg/day): " << slope_coefficient * 24 * 60 * 60 << "\n";
    }
    catch (const std::exception& err)
    {
        std::cout << "Error: " << err.what() << "\n";
    }
}
