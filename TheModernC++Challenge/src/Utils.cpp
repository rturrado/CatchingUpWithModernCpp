#include "Utils.h"

#include <algorithm>


// Check if input stream is clear
bool is_istream_clear(const std::istream& is)
{
    return (is.rdbuf()->in_avail() == 1);  // a correct input will be followed by the ENTER character
}


// Clear input stream
void clear_istream(std::istream& is)
{
    is.clear();
    if (std::streamsize n = is.rdbuf()->in_avail())  // ignores whatever there may be within is
    {
        is.ignore(n);
    }
}


// Read positive number
size_t read_positive_number(size_t lower_limit, size_t upper_limit)
{
    size_t n{ 0 };
    for (;;)
    {
        std::cout << "Please enter a number in the range [" << lower_limit << ", " << upper_limit << "): ";
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

// Read list of positive numbers
std::vector<size_t> read_list_of_positive_numbers(size_t minimum_list_size, size_t lower_limit, size_t upper_limit)
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