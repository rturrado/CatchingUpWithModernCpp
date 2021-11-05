// References:
// - Desing idioms from an alternate universe; Dr Ivan Cukic; CppCon 2021
// - C++ Data Pipes: https://dev.goodwu.net/post/2016-04-18-data-pipes/

module;

#include "Print.h"

#include <algorithm>  // transform, reduce
#include <functional>  // plus
#include <iostream>  // cout
#include <numeric>  // accumulate, iota
#include <string>  // to_string
#include <vector>

export module Composition;

template <typename C, typename F>
auto operator|(C&& c, F&& f)
{
    return f(std::forward<C>(c));
}

template <typename RT, typename F>
auto accumulate(RT&& total, F&& f)
{
    return [&total, &f](auto&& c) {
        return std::accumulate(std::cbegin(c), std::cend(c), std::forward<RT>(total), std::forward<F>(f));
    };
}

template <typename F>
auto reduce(F&& f)
{
    return [&f] (auto&& c) {
        return std::reduce(std::next(std::cbegin(c)), std::cend(c), *std::cbegin(c), std::forward<F>(f));
    };
}

template <typename F>
auto transform(F&& f)
{
    return [&f](auto&& c) {
        std::transform(std::cbegin(c), std::cend(c), std::begin(c), std::forward<F>(f));
        return c;
    };
}

export void composition_main()
{
    auto square = [](auto& n) { return n * n; };
    auto to_string = [](auto n) { return std::to_string(n); };
    
    std::vector<int> v(10);
    std::iota(std::begin(v), std::end(v), 1);
    std::cout << "v: " << v << "\n";

    auto sum_of_v{ v | reduce(std::plus<>{}) };
    std::cout << "\tSum of v: " << sum_of_v << "\n";

    auto squares_of_v{ std::vector<int>{v} | transform(square) };
    std::cout << "\tSquares of v: " << squares_of_v << "\n";

    auto sum_of_squares_of_v{ std::vector<int>{v} | transform(square) | reduce(std::plus<>{}) };
    std::cout << "\tSum of squares of v: " << sum_of_squares_of_v << "\n";

    auto v_to_string{ v | accumulate(std::string{}, [to_string](auto total, auto& n) { return total + to_string(n); }) };
    std::cout << "\tv to string: " << v_to_string << "\n";
}
