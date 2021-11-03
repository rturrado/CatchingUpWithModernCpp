#include "Chapter3_StringsAndRegularExpressions.h"
#include "Print.h"

#include <iostream>  // cout
#include <string>
#include <vector>

std::vector<std::string> split(const std::string& s, const std::string& delimiters)
{
    std::vector<std::string> ret{};
    for (size_t previous_pos{ 0 }, pos{ 0 }; pos < s.size(); )
    {
        pos = s.find_first_of(delimiters, pos);
        if (pos > previous_pos)
        {
            ret.push_back(s.substr(previous_pos, pos - previous_pos));
        }
        if (pos != std::string::npos)
        {
            ++pos;
            previous_pos = pos;
        }
    }
    return ret;
}

// Splitting a string into tokens with a list of possible delimiters
//
// Write a function that, given a string and a list of possible delimiter characters,
// splits the string into tokens separated by any of the delimiters and returns them in a std::vector.
//
// Example: "this,is.a sample!!" with delimiters ",.! ", output: { "this", "is", "a", "sample" }.
void problem_27_main()
{
    const std::string s{ "this,is.a sample!!" };
    const std::string d1{ ",.! " };
    const std::string d2{ "#" };
    std::cout << "Splitting string \"" << s << "\" into: " << split(s, d1) << "\n";
    std::cout << "Splitting string \"" << s << "\" into: " << split(s, d2) << "\n";

    std::cout << "\n";
}
