#include "Chapter11_Cryptography.h"

#include "RtcFilesystem.h"

#include <algorithm>  // transform
#include <array>
#include <bitset>
#include <cassert>  // assert
#include <cstdint>  // uint8_t
#include <filesystem>
#include <format>
#include <iostream>  // cout
#include <iterator>  // back_inserter
#include <unordered_map>
#include <span>
#include <string>
#include <string_view>
#include <vector>


class Base64
{
public:
    using value_type = uint8_t;

private:
    using encoding_table_t = std::array<unsigned char, 64>;
    using decoding_table_t = std::unordered_map<char, value_type>;
    using octet_t = std::bitset<8>;
    using octets_t = std::array<octet_t, 3>;
    using sextet_t = std::bitset<6>;
    using sextets_t = std::array<sextet_t, 4>;

    static inline const encoding_table_t encoding_table_{
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', '0', '1', '2', '3',
        '4', '5', '6', '7', '8', '9', '+', '/'
    };
    static inline const unsigned char padding{ '=' };
    static inline const size_t max_line_width{ 76 };

    static inline const decoding_table_t decoding_table_{
        {'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7},
        {'I', 8}, {'J', 9}, {'K', 10}, {'L', 11}, {'M', 12}, {'N', 13}, {'O', 14}, {'P', 15},
        {'Q', 16}, {'R', 17}, {'S', 18}, {'T', 19}, {'U', 20}, {'V', 21}, {'W', 22}, {'X', 23},
        {'Y', 24}, {'Z', 25}, {'a', 26}, {'b', 27}, {'c', 28}, {'d', 29}, {'e', 30}, {'f', 31},
        {'g', 32}, {'h', 33}, {'i', 34}, {'j', 35}, {'k', 36}, {'l', 37}, {'m', 38}, {'n', 39},
        {'o', 40}, {'p', 41}, {'q', 42}, {'r', 43}, {'s', 44}, {'t', 45}, {'u', 46}, {'v', 47},
        {'w', 48}, {'x', 49}, {'y', 50}, {'z', 51}, {'0', 52}, {'1', 53}, {'2', 54}, {'3', 55},
        {'4', 56}, {'5', 57}, {'6', 58}, {'7', 59}, {'8', 60}, {'9', 61}, {'+', 62}, {'/', 63}
    };

public:
    [[nodiscard]] std::string encode(const std::vector<value_type>& data, bool use_padding = true) const
    {
        std::string ret{};

        auto get_sextet = [](const std::bitset<24>& input_bs, size_t sextet_index) {
            std::bitset<24> sextet_mask_bs{ 0x00'00'3f };
            auto sextet_ul{ ((input_bs >> (18 - 6 * sextet_index)) & sextet_mask_bs).to_ulong() };
            return sextet_t{ sextet_ul };
        };
        auto build_sextets_from_octets = [&get_sextet](const auto& octets) {
            std::bitset<24> input_bs{
                (static_cast<unsigned long long>(octets[0].to_ulong()) << 16) +
                (static_cast<unsigned long long>(octets[1].to_ulong()) << 8) +
                octets[2].to_ulong()
            };
            return sextets_t{
                get_sextet(input_bs, 0),
                get_sextet(input_bs, 1),
                get_sextet(input_bs, 2),
                get_sextet(input_bs, 3)
            };
        };
        auto max_line_width_reached = [&ret]() {
            return ((ret.size() % max_line_width) + 4) >= max_line_width;
        };

        size_t i{ 0 };
        for (; i + 3 <= data.size(); i += 3)
        {
            auto octets{ octets_t{ data[i], data[i + 1], data[i + 2] } };
            auto sextets{ build_sextets_from_octets(octets) };
            std::ranges::transform(sextets, std::back_inserter(ret),
                [](auto& sextet) { return encoding_table_[sextet.to_ulong()]; });

            if (max_line_width_reached()) {
                ret += '\n';
            }
        }

        if (i < data.size())
        {
            auto bytes_left_to_read{ data.size() - i };

            // 1 or 2 bytes left to read
            octets_t octets{
                octet_t{ data[i] },
                (bytes_left_to_read == 2) ? octet_t{ data[i + 1] } : octet_t{},
                octet_t{}
            };
            auto sextets{ build_sextets_from_octets(octets) };

            // Add last sextets of information
            //
            // 1 byte left to read -> 2 sextets of information
            // 2 bytes left to read -> 3 sextets of information
            std::transform(std::cbegin(sextets), std::cbegin(sextets) + bytes_left_to_read + 1, std::back_inserter(ret),
                [](auto& sextet) { return encoding_table_[sextet.to_ulong()]; });

            // Add padding
            //
            // 1 byte left to read -> 2 sextets of padding
            // 2 bytes left to read -> 1 sextet of padding
            if (use_padding) {
                ret += std::string(3 - bytes_left_to_read, padding);
            }
        }

        return ret;
    }

    [[nodiscard]] std::vector<value_type> decode(std::string_view data) const
    {
        std::vector<value_type> ret{};

        auto get_octet = [](const std::bitset<24>& input_bs, size_t octet_index) {
            std::bitset<24> octet_mask_bs{ 0x00'00'ff };
            auto octet_ul{ ((input_bs >> (16 - 8 * octet_index)) & octet_mask_bs).to_ulong() };
            return octet_t{ octet_ul };
        };
        auto build_octets_from_sextets = [&get_octet](const std::bitset<24>& input_bs) {
            return octets_t{
                get_octet(input_bs, 0),
                get_octet(input_bs, 1),
                get_octet(input_bs, 2)
            };
        };
        auto decode_group = [&build_octets_from_sextets, &ret](const std::span<const value_type> group) {
            std::bitset<24> input_bs{
                (static_cast<unsigned long long>(group[0]) << 18) +
                (static_cast<unsigned long long>(group[1]) << 12) +
                (static_cast<unsigned long long>(group[2]) << 6) +
                group[3]
            };
            auto octets{ build_octets_from_sextets(input_bs) };
            std::ranges::transform(octets, std::back_inserter(ret),
                [](auto& octet) { return static_cast<value_type>(octet.to_ulong()); });
        };
        auto decode_subgroup = [&build_octets_from_sextets, &ret](const std::span<const value_type> subgroup) {
            auto characters_left_to_read{ subgroup.size()};

            // 2 or 3 characters left to read
            std::bitset<24> input_bs{
                (static_cast<unsigned long long>(subgroup[0]) << 18) +
                (static_cast<unsigned long long>(subgroup[1]) << 12) +
                ((characters_left_to_read == 3) ? (static_cast<unsigned long long>(subgroup[2]) << 6) : 0)
            };
            auto octets{ build_octets_from_sextets(input_bs) };

            // Add last octets of information
            //
            // 2 characters left to read -> 1 octet of information
            // 3 characters left to read -> 2 octets of information
            std::transform(std::cbegin(octets), std::cbegin(octets) + characters_left_to_read - 1, std::back_inserter(ret),
                [](auto& octet) { return static_cast<value_type>(octet.to_ulong()); });
        };

        for (auto i{0}; i < data.size();)
        {
            value_type chunk[4];
            size_t j{ 0 };
            for (; j < 4 and i < data.size(); ++i)
            {
                if (decoding_table_.contains(data[i]))
                {
                    chunk[j++] = decoding_table_.at(data[i]);
                }
            }
            switch(j)
            {
            case 4: decode_group(chunk); break;
            case 3:
            case 2: decode_subgroup({ chunk, j }); break;
            case 1: assert("Error: chunk.size() == 1, " and false); break;
            case 0: assert("Error: chunk.size() == 0, " and i != data.size()); break;
            default: break;
            }
        }

        return ret;
    }
};


void test_base_64(const auto& input_data, bool use_padding = true)
{
    static const auto base64{ Base64{} };
    const auto encoded_data{ base64.encode(input_data, use_padding) };
    const auto decoded_data{ base64.decode(encoded_data) };

    if (input_data == decoded_data) { std::cout << "\tOK\n"; }
    else { std::cout << "\tError: the decoded data differs from the input data\n"; }
}


// Base64 encoding and decoding
//
// Write a program that can encode and decode binary data using the base64 encoding scheme.
// You must implement the encoding and decoding functions yourself and not use a 3rd party library.
// The table used for encoding should be the one from the MIME specification.
void problem_90_main()
{
    const auto input_file_path{ std::filesystem::current_path() / "res" / "fonts" / "calibri.ttf" };
    const auto input_file_content{ rtc::filesystem::get_binary_file_content<Base64::value_type>(input_file_path) };
    std::cout << std::format("Encoding and decoding file '{}'\n", input_file_path.string());
    test_base_64(input_file_content);

    for (std::string_view input_data : { "", "M", "Ma", "Man", "Many", "Many ", "Many h", "Many hands make light work." })
    {
        for (auto use_padding : { true, false })
        {
            std::cout << std::format("Encoding and decoding text '{}'\n", input_data);
            test_base_64(std::vector<Base64::value_type>{std::cbegin(input_data), std::cend(input_data)}, use_padding);
        }
    }

    std::cout << "\n";
}
