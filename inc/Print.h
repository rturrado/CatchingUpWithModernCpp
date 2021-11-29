#ifndef PRINT_H
#define PRINT_H

#include <algorithm>  // for_each, sort
#include <concepts>
#include <iomanip>  // setfill, setw
#include <ios>  // hex
#include <ostream>
#include <utility>  // pair


// Print container
template <typename T>
concept printable = requires (std::ostream& os, const T& t) { os << t; };

template <typename C>
concept implements_operator_extraction = requires (std::ostream& os, const C& c) { os << c; };

template <typename C>
    requires (!std::same_as<typename C::value_type, uint8_t>) && (!implements_operator_extraction<C>) && printable<typename C::value_type>
std::ostream& operator<<(std::ostream& os, const C& c)
{
    os << "{";
    std::for_each(cbegin(c), cend(c), [first = true, &os](const auto& n) mutable {
        os << (first ? " " : ", ") << n; first = false;
    });
    os << " }";
    return os;
};

template <typename C>
    requires std::same_as<typename C::value_type, uint8_t> && (!implements_operator_extraction<C>)
std::ostream& operator<<(std::ostream& os, const C& c)
{
    os << "{";
    std::for_each(cbegin(c), cend(c), [first = true, &os](const auto& n) mutable {
        os << (first ? " " : ", ") << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<uint16_t>(n); first = false;
    });
    os << " }";
    return os;
};


// Print pair
template<typename T, typename U = T>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p)
{
    return os << "[" << p.first << ", " << p.second << "]";
}

#endif  // PRINT_H
