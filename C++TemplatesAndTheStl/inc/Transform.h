#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
concept Printable = requires (std::ostream& os, T t) { os << t; };

template <Printable T>
void print_vector(const std::vector<T>& v, const std::string& text = "")
{
    std::cout << text;
    bool first = true;
    std::for_each(v.begin(), v.end(), [&first](const T& x) { std::cout << (first ? "" : " ") << x; first = false; });
    std::cout << "\n";
}

template <typename T>
class Accum {
    T _acc = 0;
public:
    Accum() = default;
    explicit Accum(T n) : _acc(n) {}
    T operator()(T y) { _acc += y; return _acc; }
};

void transform_main();

#endif  // TRANSFORM_H

