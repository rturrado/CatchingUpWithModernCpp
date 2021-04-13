#include <algorithm>
#include <iostream>
#include <vector>

#include "InvalidatedIterators.h"

void print_vector(const std::vector<int>& v)
{
    size_t index = 0;
    std::for_each(v.begin(), v.end(),
        [&index](const auto n) { std::cout << index++ << ": " << n << "\n"; });
}

void push_back_while_traversing(std::vector<int>& v)
{
    std::cout << "Pushing back while traversing the vector\n";
    size_t index = 0;
    for (auto n : v)
    {
        std::cout << index++ << ": " << n << "\n";
        // push_back operation invalidates the range loop
        // We get unexpected output from the second element onwards
        // Cppcheck reports an error: Calling 'push_back' while iterating the container is invalid
        v.push_back(static_cast<int>(v.size()) + 1);
    }
    // However, the push_back operation worked correctly
    // so we can print the vector now and get the expected output
    print_vector(v);
}

void resize_while_traversing(std::vector<int>& v)
{
    std::cout << "Resizing while traversing the vector\n";
    size_t index = 0;
    for (auto n : v)
    {
        std::cout << index++ << ": " << n << "\n";
        // resize operation also invalidates the range loop
        // We get unexpected output from the second element onwards
        v.resize(v.size() + 1);
        v[v.size() - 1] = static_cast<int>(v.size());
    }
    // However, the resize operation also worked correctly
    // so we can print the vector now and get the expected output
    print_vector(v);
}

void invalidated_iterators_main()
{
    std::vector<int> v{ 1, 2 , 3 };
    
    // 1) push_back while traversing the vector
    push_back_while_traversing(v);

    // 2) resize while traversing the vector
    resize_while_traversing(v);
}
