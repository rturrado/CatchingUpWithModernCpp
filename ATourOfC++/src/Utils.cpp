#include <iostream>
#include <istream>
#include <string>
#include <vector>

#include "Utils.h"

std::vector<int> read_vector_of_numbers_from_istream(std::istream& is)
{
    std::vector<int> v;
    std::cout << "Please input a list of numbers ('quit' to finish):\n";
    for (std::string s; is >> s;)
    {
        if (s == "quit")
        {
            break;
        }
        try {
            v.push_back(std::stoi(s));
        }
        catch (const std::invalid_argument&)
        {
            std::cout << s << " is not a number. Please retry.\n";
        }
    }
    return v;  // move constructor
}

std::vector<std::string> read_vector_of_strings_from_istream(std::istream& is)
{
    std::vector<std::string> v;
    std::cout << "Please input a list of strings ('quit' to finish):\n";
    for (std::string s; is >> s; )
    {
        if (s == "quit")
        {
            break;
        }
        v.push_back(s);
    }
    return v;  // move constructor
}
