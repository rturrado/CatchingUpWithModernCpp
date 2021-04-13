#ifndef __SPAN_H__
#define __SPAN_H__

#include <algorithm>
#include <iostream>
#include <span>

template <typename T>
concept Printable = requires(std::ostream& os, T a) { os << a; };

template <Printable T>
void print_span(const std::span<T> s)
{
    bool first = true;
    std::for_each(s.begin(), s.end(), [&first](const T& x) { std::cout << (first ? "" : " ") << x; first = false; });
    std::cout << "\n";
}

void span_main();

#endif
