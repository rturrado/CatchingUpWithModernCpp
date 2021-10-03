#include <algorithm>  // transform
#include <cctype>  // isalpha
#include <filesystem>  // path
#include <format>
#include <fstream>
#include <iostream>  // cout
#include <map>
#include <numeric>  // accumulate
#include <stdexcept>  // runtime_error
#include <string>

using letter_counts = std::map<char, size_t>;

letter_counts count_letters(std::ifstream& in_file)
{
    letter_counts ret{};
    std::string line{};
    while (std::getline(in_file, line))
    {
        for (auto& c : line)
        {
            // Like all other functions from <cctype>, the behavior of std::isalpha is undefined
            // if the argument's value is neither representable as unsigned char nor equal to EOF.
            // To use these functions safely with plain chars (or signed chars),
            // the argument should first be converted to unsigned char.
            //
            // From CppReference: https://en.cppreference.com/w/cpp/string/byte/isalpha
            if (std::isalpha(static_cast<unsigned char>(c)))
            {
                ret[c]++;
            }
        }
    }
    return ret;
}

void print_histogram(letter_counts& counts)
{
    size_t total_count = std::accumulate(cbegin(counts), cend(counts), static_cast<size_t>(0), [](auto total, auto& kvp) {
        return total + kvp.second;
        });

    auto bar_width = [](double frequency, size_t line_width) {
        // Subtract 12 to the line width for char, percentage and spaces, e.g.: 'e (13.25 %) '
        return static_cast<size_t>(((line_width - 12) * frequency) / 100);
    };

    auto print_histogram_line = [&total_count, &bar_width](char c, size_t count, size_t line_width) {
        double frequency = (count * 100.0) / total_count;
        std::cout << std::format("\t{} ({:5.2f} %) {:=>{}}\n", c, frequency, '>', bar_width(frequency, line_width));
    };

    const size_t histogram_width{ 300 };
    std::for_each(cbegin(counts), cend(counts), [&print_histogram_line, &histogram_width](auto& kvp) {
        print_histogram_line(kvp.first, kvp.second, histogram_width);
    });
}

// Text histogram
//
// Write a program that, given a text, determines and prints a histogram with the frequency of each letter of the alphabet.
// The frequency is the percentage of the number of appearances of each letter from the total count of letters.
// The program should count only the appearances of letters and ignore digits, signs, and other possible characters.
// The frequency must be determined based on the count of letters and not the text size.
void problem_49_main()
{
    namespace fs = std::filesystem;

    try
    {
        fs::path in_file_path{ fs::path{ "res" } / "sample.txt" };
        std::ifstream in_file{ in_file_path };
        if (not in_file)
        {            
            throw std::runtime_error{ std::format("file not found: {}, from current path: {}",
                in_file_path.string(), fs::current_path().string()) };
        }

        // Count letters
        auto counts{ count_letters(in_file) };

        // Print histogram
        print_histogram(counts);
    }
    catch (const std::exception& err)
    {
        std::cout << "Error: " << err.what() << "\n";
    }

    std::cout << "\n";
}
