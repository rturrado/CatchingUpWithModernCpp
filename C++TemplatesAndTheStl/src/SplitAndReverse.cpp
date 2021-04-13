#include "SplitAndReverse.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

auto split(const std::string& line)
{
    std::vector<std::string> v;
    std::stringstream ss{ line };
    std::string str;
    while (ss >> str)
    {
        v.push_back(str);
    }
    return v;
}

void split_and_reverse_main()
{
    std::string str = "Hello, this is Roberto!";
    std::vector v = split(str);
    std::reverse(v.begin(), v.end());
    std::for_each(v.begin(), v.end(), [](const auto& n) { std::cout << n << "/"; });
    std::cout << "\n";
}
