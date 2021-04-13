#include "VectorOfIntsWithTrianglePattern.h"

#include <iomanip>
#include <iostream>
#include <span>
#include <vector>

void print_vector(const std::vector<int>& v, size_t width)
{
    size_t num_spaces = (width - v.size()) / 2;
    for (size_t i = 0; i < num_spaces; ++i)
    {
        std::cout << std::setw(3) << " ";
    }
    for (auto rit = v.rbegin(); rit != v.rend(); ++rit)
    {
        std::cout << std::setw(3) << *rit;
    }
    for (size_t i = 0; i < num_spaces; ++i)
    {
        std::cout << std::setw(3) << " ";
    }
    std::cout << "\n";
}

void print_pattern(std::vector<int> v)
{
    size_t width = v.size();
    while (true)
    {
        print_vector(v, width);
        if (v.size() > 2)
        {
            v.erase(v.begin() + (v.size() / 2 + 1));
            v.erase(v.begin() + (v.size() / 2 - 1));
        }
        else
        {
            break;
        }
    }
}

void vector_of_ints_with_triangle_pattern_main()
{
    std::vector<int> v1{ 0, 1, 2, 3, 4, 5 };
    std::vector<int> v2{ 0, 1, 2, 3, 4, 5, 6 };
    print_pattern(v1);
    print_pattern(v2);
}
