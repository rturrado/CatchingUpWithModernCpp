#ifndef RTC_CONSOLE_READ_H
#define RTC_CONSOLE_READ_H


#include <algorithm>  // binary_search, count_if, sort
#include <cctype>  // isdigit
#include <ios>  // dec, streamsize
#include <iostream>  // cin, cout
#include <istream>
#include <limits>  // numeric_limits
#include <ostream>
#include <stdexcept>  // invalid_argument, out_of_range
#include <string>  // stoul
#include <vector>


// Check if input stream is clear
inline bool is_istream_clear(const std::istream& is)
{
    return (is.rdbuf()->in_avail() == 1);  // a correct input will be followed by the ENTER character
}


// Clear input stream
inline void clear_istream(std::istream& is)
{
    is.clear();
    if (std::streamsize n = is.rdbuf()->in_avail())  // ignores whatever there may be within is
    {
        is.ignore(n);
    }
}


// Read a char from a possible list of options
inline char read_char(const std::string& message, std::vector<char> options)
{
    std::sort(std::begin(options), std::end(options));

    char c{};
    for (;;)
    {
        std::cout << message;
        std::cin >> c;
        if (not std::cin.fail() and
            std::binary_search(std::cbegin(options), std::cend(options), c) and
            is_istream_clear(std::cin))
        {
            std::cout << "\tOK\n";
            break;
        }
        std::cout << "\tError: invalid input\n";
        clear_istream(std::cin);
        c = 0;
    }
    clear_istream(std::cin);
    return c;
}


// Read a positive number in the range [lower_limit, upper_limit)
// or [lower_limit, SIZE_T_MAX) in case upper_limit is not specified
inline size_t read_positive_number(
    const std::string& message,
    size_t lower_limit,
    size_t upper_limit = std::numeric_limits<size_t>::max())
{
    size_t n{ 0 };
    for (;;)
    {
        std::cout << message;
        std::cin >> n;
        if (std::cin.fail())
        {
            std::cout << "\tError: invalid input\n";
        }
        else if (n < lower_limit || n >= upper_limit)
        {
            std::cout << "\tError: number not within the limits\n";
        }
        else if (is_istream_clear(std::cin))
        {
            std::cout << "\tOK\n";
            break;
        }
        clear_istream(std::cin);
        n = 0;
    }
    clear_istream(std::cin);
    return n;
}


// Read a list of positive numbers in the range [lower_limit, upper_limit)
// or [lower_limit, SIZE_T_MAX) in case upper_limit is not specified
// minimum_list_size is the minimum number of the elements to read for the list
inline std::vector<size_t> read_list_of_positive_numbers(
    size_t minimum_list_size,
    size_t lower_limit,
    size_t upper_limit = std::numeric_limits<size_t>::max())
{
    std::vector<size_t> v{};
    while (v.size() < minimum_list_size)
    {
        std::cout << "Please enter " << minimum_list_size << " or more numbers "
            << "in the range [" << lower_limit << ", " << upper_limit << ")"
            << " ('quit' to finish the list): ";
        bool valid_input{ true };
        for (std::string s{}; valid_input && std::cin >> s; )
        {
            if (s == "quit")
            {
                if (is_istream_clear(std::cin))
                {
                    break;
                }
            }
            else
            {
                try
                {
                    size_t i{ std::stoul(s) };
                    if (i < lower_limit || i >= upper_limit)
                    {
                        std::cout << "\tError: number " << i << " not within the limits\n";
                        valid_input = false;
                    }
                    else
                    {
                        v.push_back(i);
                    }
                }
                catch (const std::invalid_argument& ex)
                {
                    std::cout << "\tError: " << ex.what() << "\n";
                    valid_input = false;
                }
                catch (const std::out_of_range& ex)
                {
                    std::cout << "\tError: " << ex.what() << "\n";
                    valid_input = false;
                }
            }
        }
        if (!valid_input || std::cin.fail() || v.size() < minimum_list_size)
        {
            clear_istream(std::cin);
            v.erase(v.begin(), v.end());
        }
    }
    clear_istream(std::cin);
    return v;
}


// Read an n-digit string
inline std::string read_n_digit_string(size_t n)
{
    std::string ret{};

    bool valid_input{ false };
    while (!valid_input)
    {
        std::cout << "Please enter a " << n << " digit string: ";
        std::cin >> ret;
        if (ret.size() != n ||
            std::count_if(ret.begin(), ret.end(), [](auto& n) { return std::isdigit(n) != 0; }) != 10)
        {
            std::cout << "\tError: invalid input\n";
        }
        else
        {
            valid_input = true;
        }
        if (!valid_input)
        {
            clear_istream(std::cin);
        }
    }

    return ret;
}


#endif  // RTC_CONSOLE_READ_H
