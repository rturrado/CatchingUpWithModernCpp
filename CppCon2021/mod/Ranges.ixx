// References: Conquering C++20 Ranges; Tristan Brindle; CppCon 2021

module;

#include <algorithm>  // copy
#include <iostream>  // cout
#include <iterator>  // ostream_iterator
#include <ranges>
#include <vector>

export module Ranges;

export void ranges_main()
{
    std::vector<int> v{ 1, 2, 3, 4, 5 };
    
    // vw_1, vw_2, and vw_3 are views
    // filter_view and filter are a range adaptors
    auto vw_1{ std::ranges::filter_view(v, [](int n) { return (n % 2 == 0); }) };
    std::ranges::copy(vw_1, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    auto vw_2{ std::ranges::views::filter(v, [](int n) { return (n % 2 == 0); }) };
    std::ranges::copy(vw_2, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    auto vw_3{ v | std::ranges::views::filter([](int n) { return (n % 2 == 0); }) };
    std::ranges::copy(vw_3, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
}
