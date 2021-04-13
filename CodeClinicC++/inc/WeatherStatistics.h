#ifndef __WEATHER_STATISTICS_H__
#define __WEATHER_STATISTICS_H__

#include <ctime>
#include <fstream>
#include <exception>
#include <map>
#include <string>

struct TimePointRange
{
    std::time_t begin{ -1 };
    std::time_t end{ -1 };
};

class HeaderFormatException : public std::exception
{
public:
    explicit HeaderFormatException(const std::string& message) : std::exception(message.c_str()) {}
};

class DataFolderNotFoundException : public std::exception
{
public:
    explicit DataFolderNotFoundException(const std::string& message) : std::exception(message.c_str()) {}
};

struct WeatherDataEntry
{
    float air_temperature{ 0.0 };
    float barometric_presure{ 0.0 };
    float dew_point{ 0.0 };
    float relative_humidity{ 0.0 };
    float wind_direction{ 0.0 };
    float wind_gust{ 0.0 };
    float wind_speed{ 0.0 };
};

class WeatherData
{
public:
    WeatherData() { read_data_files(); };
    ~WeatherData() {};

    std::time_t get_first_time_point();
    std::time_t get_last_time_point();
    float calculate_barometric_pressure_slope_coefficient(const TimePointRange& time_point_range);
private:
    void read_data_files();
    void read_header(std::ifstream& ifs);
    void read_data_file(std::ifstream& data_file_fs);

    std::map<std::time_t, WeatherDataEntry> data_{};
};

std::time_t to_time_t(const std::string& date, const std::string& time);
std::string time_t_to_string(std::time_t time_point);

void weather_statistics_main();

#endif
