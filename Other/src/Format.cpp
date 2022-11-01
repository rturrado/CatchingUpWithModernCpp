#include "Format.h"

#include <chrono>
#include <cstdio>
#include <fmt/chrono.h>
#include <fmt/core.h>
#include <fmt/ostream.h>
#include <format>
#include <iomanip>  // setprecision
#include <ios>  // fixed
#include <iostream>
#include <sstream>
#include <string>

namespace ch = std::chrono;

template <typename F>
auto measure(F&& f) {
    std::ostringstream oss{};
    std::string s(1'000, 'a');
    auto d{ 3.14 };
    auto i{ 42 };
    auto start{ ch::steady_clock::now() };
    for (int j{ 1'000'000 }; j >= 0; --j) {
        f(oss, s, d, i);
    }
    auto end{ ch::steady_clock::now() };
    return ch::duration_cast<ch::milliseconds>(end - start);
}

void format_main() {
    auto s{ "hello!" };
    auto d{ 3.14 };
    auto i{ 42 };

    // 1) Format string even shorter than printf's, and far clearer than "the chevron hell"
    // 2) No need to specify type of arguments (e.g. %s, %d...)
    printf("printf> string: '%s', double: %0.5f, int: %d\n", s, d, i);
    std::cout
        << "streams> "
        << "string: '" << s << "'"
        << ", double: " << std::fixed << std::setprecision(5) << d
        << ", int: " << i << "\n";
    std::cout << std::format("format> string: '{}', double: {:0.5f}, int: {}\n", s, d, i);
    fmt::print("fmt::print> string: '{}', double: {:0.5f}, int: {}\n\n", s, d, i);

    // 3) No sticky flags
    std::cout
        << "streams> "
        << std::hex << "i (hex): " << i
        << ", i (dec): " << i
        << ", i (really dec): " << std::dec << i << "\n";
    std::cout << std::format("format> i (hex): {0:x}, i (dec): {0:}\n\n", i);
    // Note that we are referring twice to the same parameter in the format specification

    // 4) Efficiency: format is reportedly (not in these tests)
    //    faster than printf, and
    //    10x times faster than streams
    // 5) Chrono format specification: direct support for printing chrono types
    std::cout << std::format(
        "Benchmarking:\n"
        "\tprintf> {}\n"
        "\tstreams> {}\n"
        "\tformat> {}\n"
        "\tfmt::print> {}\n\n",
        measure([]([[maybe_unused]] std::ostream& os, const std::string& s, double d, int i) {
            static char buf[1048];
            sprintf_s(buf, "string: '%s', double: %0.5f, int: %d\n", s.data(), d, i);
        }),
        measure([](std::ostream& os, const std::string& s, double d, int i) {
                os
                    << "string: '" << s << "'"
                    << ", double: " << std::fixed << std::setprecision(5) << d
                    << ", int: " << i << "\n";
        }),
        measure([](std::ostream& os, const std::string& s, double d, int i) {
            os << std::format("string: '{}', double: {:0.5f}, int: {}\n", s, d, i);
        }),
        measure([](std::ostream& os, const std::string& s, double d, int i) {
            fmt::print(os, "string: '{}', double: {:0.5f}, int: {}\n", s, d, i);
        })
    );
}
