// References: Desing idioms from an alternate universe; Dr Ivan Cukic; CppCon 2021

module;

#include "Print.h"

#include <concepts>  // invocable
#include <functional>  // invoke
#include <iostream>  // cout
#include <type_traits>  // invoke_result_t
#include <utility>  // forward
#include <vector>

export module Composition;

/*
template <typename F, typename G>
    requires std::invocable<F> and std::invocable<G>
auto compose(F&& f, G&& g)
{
    return [f, g](auto&&... args) {
        auto g_res = std::invoke(std::forward<G>(g), std::forward<decltype(args)>(args)...);
        auto f_res = std::invoke(std::forward<F>(f), g_res);
        return f_res;
    };
}

auto compose = [](auto f, auto g) {
    return [=](auto&&... x) {
        return f(g(x...));
    };
};
*/

export void composition_main()
{
    auto my_transform = [](int n) { return n * n; };
    auto my_reduce = [](int total, int n) { return total + n; };
    //auto my_transform_reduce = compose(my_reduce, my_transform);
    std::vector<int> v{ 1, 2, 3, 4, 5 };
    //std::cout << "Sum of squares of v: " << my_transform_reduce(v) << "\n";
    std::cout << v << "\n";
}
