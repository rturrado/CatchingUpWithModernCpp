#ifndef PRETTY_PRINT_H
#define PRETTY_PRINT_H

#include <algorithm>  // fill_n
#include <iterator>  // ostream_iterator
#include <ostream>
#include <string>

struct FillLineStart
{
    size_t level{};
    std::string value{ "    " };
};

inline std::ostream& operator<<(std::ostream& os, const FillLineStart& fill)
{
    std::fill_n(std::ostream_iterator<std::string>(os), fill.level, fill.value);
    return os;
}

inline FillLineStart operator+(const FillLineStart& fill, size_t increase)
{
    return FillLineStart{ fill.level + increase, fill.value };
}

inline FillLineStart operator+(size_t increase, const FillLineStart& fill)
{
    return fill + increase;
}

#endif  // PRETTY_PRINT_H
