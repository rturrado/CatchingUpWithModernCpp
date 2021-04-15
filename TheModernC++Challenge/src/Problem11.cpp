#include <cassert>
#include <map>
#include <tuple>
#include <string>
#include <string_view>

#include "Chapter1_MathProblems.h"
#include "Utils.h"

enum class DigitPosition : std::size_t
{
    Units,
    Tens,
    Hundreds,
    Thousands
};

namespace P11_V1
{
    std::string thousands_to_roman(size_t n)
    {
        switch (n)
        {
        case 0: return "";
        case 1: return "M";
        case 2: return "MM";
        case 3: return "MMM";
        default: throw std::out_of_range("Trying to convert to Roman numeral a number equal or bigger than 4000"); break;
        }
    }

    std::string hundreds_to_roman(size_t n)
    {
        switch (n)
        {
        case 0: return "";
        case 1: return "C";
        case 2: return "CC";
        case 3: return "CCC";
        case 4: return "CD";
        case 5: return "D";
        case 6: return "DC";
        case 7: return "DCC";
        case 8: return "DCCC";
        case 9: return "CM";
        default: assert(0 <= n && n <= 9); return "";
        }
    }

    std::string tens_to_roman(size_t n)
    {
        switch (n)
        {
        case 0: return "";
        case 1: return "X";
        case 2: return "XX";
        case 3: return "XXX";
        case 4: return "XL";
        case 5: return "L";
        case 6: return "LX";
        case 7: return "LXX";
        case 8: return "LXXX";
        case 9: return "XC";
        default: assert(0 <= n && n <= 9); return "";
        }
    }

    std::string units_to_roman(size_t n)
    {
        switch (n)
        {
        case 0: return "";
        case 1: return "I";
        case 2: return "II";
        case 3: return "III";
        case 4: return "IV";
        case 5: return "V";
        case 6: return "VI";
        case 7: return "VII";
        case 8: return "VIII";
        case 9: return "IX";
        default: assert(0 <= n && n <= 9); return "";
        }
    }
}

namespace P11_V2
{
    std::map<DigitPosition, std::tuple<char, char, char>> romanLettersForDigitPosition{
        {DigitPosition::Thousands, {'M', ' ', ' '}},
        {DigitPosition::Hundreds, {'C', 'D', 'M'}},
        {DigitPosition::Tens, {'X', 'L', 'C'}},
        {DigitPosition::Units, {'I', 'V', 'X'}},
    };

    std::string to_roman(size_t n, DigitPosition dp)
    {
        if (dp == DigitPosition::Thousands && n > 3)
        {
            throw std::out_of_range("Trying to convert to Roman numeral a number equal or bigger than 4000");
        }

        std::string one{ get<0>(romanLettersForDigitPosition[dp]) };
        std::string five{ get<1>(romanLettersForDigitPosition[dp]) };
        std::string ten{ get<2>(romanLettersForDigitPosition[dp]) };

        switch (n)
        {
        case 0: return "";
        case 1: return one;
        case 2: return one + one;
        case 3: return one + one + one;
        case 4: return one + five;
        case 5: return five;
        case 6: return five + one;
        case 7: return five + one + one;
        case 8: return five + one + one + one;
        case 9: return one + ten;
        default: assert(0 <= n && n <= 9); return "";
        }
    };
}

namespace P11_V3
{
    constexpr std::string_view romanNumeralLetters{ "IVXLCDM" };
    constexpr std::string_view getRomanLettersForDigitPosition(const DigitPosition& dp)
    {
        size_t pos{ static_cast<size_t>(dp) * 2 };
        size_t count{ (dp == DigitPosition::Thousands) ? 1u : 3u };
        return romanNumeralLetters.substr(pos, count);
    }

    std::string to_roman(size_t n, DigitPosition dp)
    {
        if (dp == DigitPosition::Thousands && n > 3)
        {
            throw std::out_of_range("Trying to convert to Roman numeral a number equal or bigger than 4000");
        }

        std::string one{ getRomanLettersForDigitPosition(dp)[0] };
        std::string five{};
        std::string ten{};
        if (dp != DigitPosition::Thousands)
        {
            five = getRomanLettersForDigitPosition(dp)[1];
            ten = getRomanLettersForDigitPosition(dp)[2];
        }

        switch (n)
        {
        case 0: return "";
        case 1: return one;
        case 2: return one + one;
        case 3: return one + one + one;
        case 4: return one + five;
        case 5: return five;
        case 6: return five + one;
        case 7: return five + one + one;
        case 8: return five + one + one + one;
        case 9: return one + ten;
        default: assert(0 <= n && n <= 9); return "";
        }
    };
}

std::string to_roman(size_t n)
{
    std::string ret{};
    size_t thousands{ n / 1000 };
    size_t hundreds{ (n % 1000) / 100 };
    size_t tens{ (n % 100) / 10 };
    size_t units{ n % 10 };

    ret = P11_V1::thousands_to_roman(thousands)
        + P11_V1::hundreds_to_roman(hundreds)
        + P11_V1::tens_to_roman(tens)
        + P11_V1::units_to_roman(units);

/*
    ret = P11_V2::to_roman(thousands, DigitPosition::Thousands)
        + P11_V2::to_roman(hundreds, DigitPosition::Hundreds)
        + P11_V2::to_roman(tens, DigitPosition::Tens)
        + P11_V2::to_roman(units, DigitPosition::Units);

    ret = P11_V3::to_roman(thousands, DigitPosition::Thousands)
        + P11_V3::to_roman(hundreds, DigitPosition::Hundreds)
        + P11_V3::to_roman(tens, DigitPosition::Tens)
        + P11_V3::to_roman(units, DigitPosition::Units);
*/

    return ret;
}

// Converting numercial values to Roman
// Write a program that, given a number entered by the user, prints its Roman numeral equivalent
void problem_11_main()
{
    // Read a positive number
    size_t n{ read_positive_number(0, 4000) };

    // Print the prime factors of that number
    std::cout << "Number\tRoman numeral equivalent\n";
    std::cout << n << "\t" << to_roman(n) << "\n";
}
