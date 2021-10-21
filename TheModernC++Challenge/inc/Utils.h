#ifndef __UTILS_H__
#define __UTILS_H__

#include <algorithm>  // for_each, sort
#include <cmath>  // sqrt
#include <chrono>
#include <concepts>
#include <iomanip>  // setfill, setw
#include <ios>  // hex
#include <iostream>
#include <limits>  // numeric_limits
#include <ostream>
#include <string>
#include <utility>  // pair
#include <vector>


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


// Check if input stream is clear
bool is_istream_clear(const std::istream& is);


// Clear input stream
void clear_istream(std::istream& is);


// Read a positive number in the range [lower_limit, upper_limit)
// or [lower_limit, SIZE_T_MAX) in case upper_limit is not specified
size_t read_positive_number(size_t lower_limit, size_t upper_limit = std::numeric_limits<size_t>::max());


// Read a list of positive numbers in the range [lower_limit, upper_limit)
// or [lower_limit, SIZE_T_MAX) in case upper_limit is not specified
// minimum_list_size is the minimum number of the elements to read for the list
std::vector<size_t> read_list_of_positive_numbers(size_t minimum_list_size, size_t lower_limit,
    size_t upper_limit = std::numeric_limits<size_t>::max());


// Read a n-digit string
std::string read_n_digit_string(size_t n);


// Check if a number is prime or not
template <typename T>
bool is_prime(const T n)
{
    for (T i = 2; i < n; ++i)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}


// Return the list of prime factors of a given number
template <typename T>
auto prime_factors(T n)
{
    std::vector<T> ret{ 1 };
    while (n > 1)
    {
        T i = 2;
        for (; i < n; ++i)
        {
            if ((n % i == 0) && is_prime(i))
            {
                break;
            }
        }
        ret.push_back(i);
        n /= i;
    }
    return ret;
}


// Return the list of divisors of a given number
template <typename T>
auto divisors(const T n)
{
    std::vector<T> ret{ 1 };
    for (T i = 2; i <= std::sqrt(n); ++i)
    {
        if (n % i == 0)
        {
            T j{ n / i };
            ret.push_back(i);
            if (i != j)
            {
                ret.push_back(j);
            }
        }
    }
    std::sort(ret.begin(), ret.end());
    return ret;
}


// Return the list of divisors of a given number
template <typename T>
T divisors_sum(const T n)
{
    T ret{ 1 };
    for (T i = 2; i <= std::sqrt(n); ++i)
    {
        if (n % i == 0)
        {
            T j{ n / i };
            ret += (i == j) ? i : (i + j);
        }
    }
    return ret;
}


namespace TMP
{
    // I couldn't use the more efficient version of divisors starting from sqrt(N) and adding j=N/I when I!=j
    // <--- std::sqrt is not constexpr

    template <size_t N, size_t I>
    struct divisors_sum_helper
    {
    public:
        static constexpr size_t value = ((N % I == 0) ? I : 0) + divisors_sum_helper<N, I - 1>::value;
    };
    template <size_t N>
    struct divisors_sum_helper<N, 1>
    {
        static constexpr size_t value = 1;
    };
    template <size_t N>
    struct divisors_sum : divisors_sum_helper<N, N / 2> {};

    template <size_t N>
    struct amicable
    {
    private:
        static constexpr size_t m = divisors_sum<N>::value;
        static constexpr size_t p = divisors_sum<m>::value;
    public:
        static constexpr bool has_amicable = (N == p);
        static constexpr size_t value = m;
    };
}  // namespace TMP


template <
    typename Time = std::chrono::microseconds,
    typename Clock = std::chrono::high_resolution_clock>
struct function_timer
{
    template <typename F, typename... Args>
    static Time duration(F&& f, Args... args)
    {
        auto start = Clock::now();

        std::invoke(std::forward<F>(f), std::forward<Args>(args)...);

        auto end = Clock::now();

        return std::chrono::duration_cast<Time>(end - start);
    }
};

#endif
