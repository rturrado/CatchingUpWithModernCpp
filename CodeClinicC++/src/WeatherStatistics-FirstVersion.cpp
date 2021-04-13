#include "WeatherStatistics.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <ctime>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>

using namespace std::filesystem;

const path g_data_folder{ "D:\\Programacion\\doc\\c++\\Code Clinic C++\\Exercise Files\\CH01\\resources" };
const std::array<std::string, 9> g_header_strings{ "date", "time", "Air_Temp", "Barometric_Press", "Dew_Point", "Relative_Humidity", "Wind_Dir", "Wind_Gust", "Wind_Speed" };

class HeaderFormatException : public std::exception
{
public:
    explicit HeaderFormatException(const std::string& message) : std::exception(message.c_str()) {}
};

class TimePoint
{
public:
    TimePoint() = default;
    TimePoint(const std::string& date, const std::string& time) : date_{ date }, time_{ time } {}
    TimePoint(const TimePoint& tp) : date_{ tp.date_ }, time_{tp.time_} {}
    TimePoint(TimePoint&& tp) : date_{ std::move(tp.date_) }, time_{std::move(tp.time_) } {}
    TimePoint& operator=(const TimePoint& tp)
    {
        date_ = tp.date_;
        time_ = tp.time_;
        return *this;
    }
    TimePoint& operator=(TimePoint&& tp)
    {
        date_ = std::move(tp.date_);
        time_ = std::move(tp.time_);
        return *this;
    }
    ~TimePoint() = default;
    float to_float() const
    {
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;

        std::string date_copy{ date_ };
        std::transform(date_.begin(), date_.end(), date_copy.begin(), [](const char& c) {return (c == '_' ? ' ' : c); });
        std::istringstream ss_date{ date_copy };
        ss_date >> year >> month >> day;

        std::string time_copy{ time_ };
        std::transform(time_.begin(), time_.end(), time_copy.begin(), [](const char& c) {return (c == ':' ? ' ' : c); });
        std::istringstream ss_time{ time_copy };
        ss_time >> hour >> minute >> second;

        return static_cast<float>(
            second +
            minute * 60 +
            hour * 60 * 60 +
            day * 24 * 60 * 60 +
            month * 30 * 24 * 60 * 60 +
            year * 365 * 30 * 24 * 60 * 60);
    }
    friend bool operator<(const TimePoint& lhs, const TimePoint& rhs);
    friend bool operator>(const TimePoint& lhs, const TimePoint& rhs);
    friend bool operator<=(const TimePoint& lhs, const TimePoint& rhs);
    friend bool operator>=(const TimePoint& lhs, const TimePoint& rhs);
    friend bool operator==(const TimePoint& lhs, const TimePoint& rhs);
    friend bool operator!=(const TimePoint& lhs, const TimePoint& rhs);
private:
    std::string date_{};
    std::string time_{};
};

bool operator<(const TimePoint& lhs, const TimePoint& rhs)
{
    return lhs.date_ < rhs.date_ || (lhs.date_ == rhs.date_ && lhs.time_ < rhs.time_);
}
bool operator>(const TimePoint& lhs, const TimePoint& rhs)
{
    return lhs.date_ > rhs.date_ || (lhs.date_ == rhs.date_ && lhs.time_ > rhs.time_);
}
bool operator<=(const TimePoint& lhs, const TimePoint& rhs)
{
    return lhs < rhs || lhs == rhs;
}
bool operator>=(const TimePoint& lhs, const TimePoint& rhs)
{
    return lhs > rhs || lhs == rhs;
}
bool operator==(const TimePoint& lhs, const TimePoint& rhs)
{
    return lhs.date_ == rhs.date_ && lhs.time_ == rhs.time_;
}
bool operator!=(const TimePoint& lhs, const TimePoint& rhs)
{
    return !(lhs == rhs);
}

struct WeatherDataEntry
{
    TimePoint time_point{};
    float air_temperature{ 0.0 };
    float barometic_presure{ 0.0 };
    float dew_point{ 0.0 };
    float relative_humidity{ 0.0 };
    float wind_direction{ 0.0 };
    float wind_gust{ 0.0 };
    float wind_speed{ 0.0 };
};
using WeatherDataVector = std::vector<WeatherDataEntry>;

void read_header(std::ifstream& ifs)
{
    for (size_t i = 0; i < g_header_strings.size(); ++i)
    {
        std::string temp_str;
        ifs >> temp_str;
        if (temp_str != g_header_strings[i])
        {
            throw HeaderFormatException(temp_str + " != " + g_header_strings[i]);
        }
    }
}

std::time_t build_clock_from_date_and_time_strings(const std::string& date, const std::string& time)
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

void read_data(std::ifstream& data_file_fs, WeatherDataVector& weather_data_vector)
{
    while (!data_file_fs.eof())
    {
        WeatherDataEntry entry;
        std::string entry_date{};
        std::string entry_time{};
        data_file_fs >> entry_date >> entry_time >> entry.air_temperature >> entry.barometic_presure >>
            entry.dew_point >> entry.relative_humidity >> entry.wind_direction >> entry.wind_gust >> entry.wind_speed;
        entry.time_point = TimePoint(entry_date, entry_time);
        weather_data_vector.push_back(entry);
    }
}

WeatherDataVector read_data_files()
{
    WeatherDataVector ret;

    // Walk all files in a given folder
    if (is_directory(g_data_folder))
    {
        std::cout << "Reading data folder: " << g_data_folder << "\n";
        for (const directory_entry& x : directory_iterator{ g_data_folder })
        {
            std::cout << "Reading data file: " << x.path() << "\n";

            // Open file
            std::ifstream data_file_fs{ x };
            // Read header
            read_header(data_file_fs);
            // Read data
            read_data(data_file_fs, ret);
            // Close file
            data_file_fs.close();
        }
    }

    return ret;
}

float calculate_slope_coefficient(const std::vector<float>& xx, const std::vector<float>& yy)
{
    assert(xx.size() == yy.size());
    size_t n = xx.size();

    double sum_xx = std::accumulate(xx.begin(), xx.end(), 0.0);
    double sum_yy = std::accumulate(yy.begin(), yy.end(), 0.0);
    float mean_xx = static_cast<float>(sum_xx / n);
    float mean_yy = static_cast<float>(sum_yy / n);

    std::vector<double> xx_times_yy(n);
    std::transform(xx.begin(), xx.end(), yy.begin(), xx_times_yy.begin(), [](const float x, const float y) { return x * y; });
    double sum_xx_times_yy = std::accumulate(xx_times_yy.begin(), xx_times_yy.end(), 0.0);
    sum_xx_times_yy -= n * mean_xx * mean_yy;

    std::vector<double> xx_times_xx(n);
    std::transform(xx.begin(), xx.end(), xx_times_xx.begin(), [](const float x) { return x * x; });
    double sum_xx_times_xx = std::accumulate(xx_times_xx.begin(), xx_times_xx.end(), 0.0);
    sum_xx_times_xx -= n * mean_xx * mean_xx;

    float b1 = static_cast<float>(sum_xx_times_yy / sum_xx_times_xx);
    float b0 = mean_yy - b1 * mean_xx;

    return b1;
}

float calculate_barometric_pressure_slope_coefficient(
    const WeatherDataVector& data_vector,
    const TimePoint& begin_time_point,
    const TimePoint& end_time_point)
{
    // Get iterators to begin and end positions
    auto begin_it = std::find_if(data_vector.begin(), data_vector.end(),
        [&begin_time_point](const WeatherDataEntry& a) {
            return a.time_point >= begin_time_point;
        });
    auto end_it = std::find_if(data_vector.begin(), data_vector.end(),
        [&end_time_point](const WeatherDataEntry& a) {
            return a.time_point > end_time_point;
        });
    // Extract times and barometric_pressures
    std::vector<float> times{};
    std::vector<float> barometric_pressures{};
    float initial_time = ((*begin_it).time_point.to_float());
    std::for_each(begin_it, end_it, [&times, &barometric_pressures, &initial_time](const WeatherDataEntry& e) {
        times.push_back(static_cast<float>(e.time_point.to_float()) - initial_time);
        barometric_pressures.push_back(e.air_temperature);
        });
    // Calculate slope coefficient
    return calculate_slope_coefficient(times, barometric_pressures);
}

void weather_statistics_main()
{
    try
    {
        // Read data files into a vector of data
        std::cout << "Reading data...\n";
        WeatherDataVector data_vector = read_data_files();

        // Sort vector
        std::cout << "Sorting data by time...\n";
        sort(data_vector.begin(), data_vector.end(),
            [](const WeatherDataEntry& a, const WeatherDataEntry& b) { return a.time_point < b.time_point; });

        // Read begin and end date and times
        std::string begin_date{};
        std::string begin_time{};
        std::string end_date{};
        std::string end_time{};
        std::cout << "Please input begin date, begin time, end date, end time (YYYY_MM_DD and HH:MM:SS formats): ";
        std::cin >> begin_date >> begin_time >> end_date >> end_time;
        std::time_t begin_date_and_time = build_clock_from_date_and_time_strings(begin_date, begin_time);
        std::time_t end_date_and_time = build_clock_from_date_and_time_strings(end_date, end_time);

        // Calculate barometric pressure slope
        TimePoint begin_time_point{ begin_date, begin_time };
        TimePoint end_time_point{ end_date, end_time };
        float slope_coefficient = calculate_barometric_pressure_slope_coefficient(data_vector, begin_time_point, end_time_point);
        std::cout << "Slope coefficient: " << slope_coefficient << "\n";
    }
    catch (const std::exception& err)
    {
        std::cout << "Error: " << err.what() << "\n";
    }
}
