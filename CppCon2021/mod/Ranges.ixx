// References:
// - Conquering C++20 Ranges; Tristan Brindle; CppCon 2021
// - C++20 Ranges — Complete Guide: https://itnext.io/c-20-ranges-complete-guide-4d26e3511db0

module;

#include "Print.h"

#include <algorithm>  // copy, sort
#include <concepts>  // integral
#include <iostream>  // cout
#include <iterator>  // ostream_iterator
#include <list>
#include <ostream>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/cycle.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/indices.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/view/zip.hpp>
#include <ranges>
#include <string>  // to_string
#include <string_view>
#include <vector>

export module Ranges;

struct Point3
{
    int x_{};
    int y_{};
    int z_{};
};

std::ostream& operator<<(std::ostream& os, const Point3& p)
{
    os << "(" << p.x_ << ", " << p.y_ << ", " << p.z_ << ")";
    return os;
}

export void ranges_main()
{
    auto even = [](std::integral auto n) { return (n % 2 == 0); };
    auto odd = [](std::integral auto n) { return (n % 2 != 0); };

    // vw_1, vw_2, and vw_3 are views
    // filter_view and filter are a range adaptors
    {
        std::vector<int> v{ 1, 2, 3, 4, 5 };

        auto vw_1{ std::ranges::filter_view(v, even) };
        std::ranges::copy(vw_1, std::ostream_iterator<int>(std::cout, " "));
        std::cout << "\n";

        auto vw_2{ std::ranges::views::filter(v, even) };
        std::ranges::copy(vw_2, std::ostream_iterator<int>(std::cout, " "));
        std::cout << "\n";

        auto vw_3{ v | std::ranges::views::filter(even) };
        std::ranges::copy(vw_3, std::ostream_iterator<int>(std::cout, " "));
        std::cout << "\n";
    }

    // Error messages
    //
    // Ranges rely on concepts to specify what types of parameters can participate in each overload
    // Therefore, making a mistake when using ranges will lead to shorter and more to the point error messages
    {
        std::list<char> l{ 'a', 'b', 'c', 'd', 'e' };
        //std::sort(std::begin(l), std::end(l));  // Error: '_Sort_unchecked': no matching overloaded function found
        //std::ranges::sort(l);  // Error: associated constraints are not satisfied (requires sortable<iterator_t<_Rng>, _Pr, _Pj>)
        std::ranges::copy(l, std::ostream_iterator<char>(std::cout, " "));
        std::cout << "\n";
    }

    // Sentinel
    //
    // For a range, end() doesn't need to return an iterator; it may return a sentinel
    // A sentinel is comparable with the iterator returned by begin()
    // 
    // In the example below:
    // - The std::unreachable_sentinel always returns false when compared to an iterator
    // - The compiler can therefore optimize out the boundary check it != end since this expression will always be true
    {
        std::string_view sv{ "What's the story?\nMorning glory!\n" };  // guaranteed to contain '\n'
        auto it{ std::ranges::find(std::begin(sv), std::unreachable_sentinel, '\n') };
        std::ranges::copy(std::begin(sv), it, std::ostream_iterator<char>(std::cout));
        std::cout << "\n";
    }

    // Projections
    //
    // A projection is a unary invocable that is applied to every element
    // An invocable is an extension of callable and also accepts member pointers
    {
        Point3 p1{ 10, 10, 10 };
        Point3 p2{ 5, 15, 25 };
        Point3 p3{ -10, 10, -10 };
        std::vector<Point3> points{ p1, p2, p3 };
        std::ranges::sort(points, std::less<>{}, & Point3::x_);
        for (auto&& p : points) { std::cout << p << " "; }
        std::cout << "\n";
    }

    // Dangling iterators
    //
    // When a range-based algorithm is invoked with a temporary range that owns its elements,
    // the algorithm will return a special iterator std::ranges::dangling
    {
        auto n{ 1234567890 };
        //auto str_it{ std::ranges::find(std::to_string(n), '0') };  // error: string is an owning range
        //std::cout << *str_it << "\n";
        
        auto str{ "1234567890" };
        auto sv_it{ std::ranges::find(std::string_view(str), '0') };  // OK: string_view is a non-owning range
        std::cout << *sv_it << "\n";
    }

    // Views
    //
    // Views are simply ranges that are cheap to copy and move (in constant time)
    // Because of this, a view cannot own the elements it is viewing
    // One exception is std::views::single which owns the single element it is viewing
    // Note that while views do not own their elements, they do not change the mutability of underlying data
    // 
    // In the example below:
    // - We pipe a vector into a view that filters out the even numbers,
    // - then we modify the odd numbers
    {
        std::vector<int> v{ 1, 2, 3, 4, 5 };
        for (auto& n : v | std::ranges::views::filter(odd)) { n--; }
        std::ranges::copy(v, std::ostream_iterator<int>(std::cout, " "));
        std::cout << "\n";
    }

    // Cycle (range/v3)
    {
        namespace rv3 = ranges;

        std::vector<int> v{ 1, 2, 3 };
        const auto seq{ v | rv3::views::cycle };  // 1, 2, 3, 1, 2, 3...
        auto seq_first_n = [&seq](size_t n) {
            return seq
                | rv3::views::take(n);
        };  // first n elements of sequence
        
        for (auto&& n : seq_first_n(9)) { std::cout << n << " "; }
        std::cout << "\n";
    }

    // Indices (range/v3)
    {
        namespace rv3 = ranges;

        auto first_n_odd = [&odd](size_t n) {
            return rv3::views::indices
                | rv3::views::filter(odd)
                | rv3::views::take(n);
        };  // 1, 3, 5... nth odd number
        
        for (auto&& n : first_n_odd(5)) { std::cout << n << " "; }
        std::cout << "\n";
    }

    // Zip (range/v3)
    {
        namespace rv3 = ranges;

        const int size{ 26 };
        const auto letters{ rv3::views::iota('a') | rv3::views::take(size) };
        const auto numbers{ rv3::views::indices | rv3::views::take(size) };
        const auto pairs{ rv3::views::zip(letters, numbers) | rv3::to<std::vector> };
        std::cout << pairs << "\n";
    }
}
