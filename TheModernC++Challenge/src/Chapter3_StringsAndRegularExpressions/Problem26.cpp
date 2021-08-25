#include <algorithm>
#include <array>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "Utils.h"

template <typename Container>
std::string join(const Container& c, const std::string& delimiter)
{
    std::string ret{};
    std::for_each(cbegin(c), cend(c), [first=true, &ret, &delimiter](const std::string& s) mutable {
        ret += (first ? "" : delimiter); first = false; ret += s;
    });
    return ret;
}

// Joining strings together separated by a delimiter
//
// Write a function that, given a list of strings and a delimiter, creates a new string
// by concatenating all the input strings separated with the specified delimiter.
// The delimiter must not appear after the last string, and when no input string is provided,
// the function must return an empty string.
//
// Example: input { "this", "is", "an", "example" } and delimiter ' ' (space), output: "this is an example".
void problem_26_main()
{
    std::vector<std::string> v{ "this", "is", "an", "example" };
    std::list<std::string> l{ "yet", "another", "one!" };
    std::array<std::string, 0> a0{};
    std::array<std::string, 1> a1{ "Joe" };

    std::string d1{ " " };
    std::cout << "Joining " << v << " with delimiter \"" << d1 << "\": " << join(v, d1) << "\n";

    std::string d2{ "---" };
    std::cout << "Joining " << l << " with delimiter \"" << d2 << "\": " << join(l, d2) << "\n";

    std::string d3{ "#" };
    std::cout << "Joining " << a0 << " with delimiter \"" << d3 << "\": " << join(a0, d3) << "\n";
    std::cout << "Joining " << a1 << " with delimiter \"" << d3 << "\": " << join(a1, d3) << "\n";

    std::cout << "\n";
}
