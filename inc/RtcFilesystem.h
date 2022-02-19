#ifndef RTC_FILESYSTEM_H
#define RTC_FILESYSTEM_H

#include <algorithm>  // copy, sort
#include <cstdint>  // uint8_t
#include <filesystem>
#include <functional>  // logical_and
#include <fstream>  // ifstream
#include <iterator>  // back_inserter, istreambuf_iterator
#include <numeric>  // transform_reduce
#include <stdexcept>  // runtime_error
#include <string>
#include <vector>

namespace fs = std::filesystem;


namespace rtc::filesystem
{
    struct FilePathDoesNotExistError : public std::runtime_error
    {
        FilePathDoesNotExistError(const std::string& path) : std::runtime_error{ message_ + path } {}
    private:
        static inline std::string message_{ "file path does not exist: " };
    };

    template <typename T = std::uint8_t>
    auto get_binary_file_content(const fs::path& file_path)
    {
        std::ifstream ifs{ file_path, std::ios::in | std::ios::binary };
        std::vector<T> content{ std::istreambuf_iterator{ifs}, {} };
        return content;
    };

    inline auto get_text_file_content(const fs::path& file_path)
    {
        std::ifstream ifs{ file_path, std::ios::in };
        std::string content{ std::istreambuf_iterator{ifs}, {} };
        return content;
    };

    inline bool are_filesystem_entries_equal(const fs::path& path_1, const fs::path& path_2)
    {
        if (path_1.filename() != path_2.filename()) { return false; }

        return get_binary_file_content(path_1) == get_binary_file_content(path_2);
    }

    inline bool are_filesystem_trees_equal(const fs::path& path_1, const fs::path& path_2)
    {
        if (not fs::exists(path_1)) { throw FilePathDoesNotExistError{ path_1.generic_string() }; }
        if (not fs::exists(path_2)) { throw FilePathDoesNotExistError{ path_2.generic_string() }; }

        if (fs::is_regular_file(path_1))
        {
            return fs::is_regular_file(path_2) and are_filesystem_entries_equal(path_1, path_2);
        }
        else if (fs::is_directory(path_1))
        {
            std::vector<fs::path> entries_1{};
            std::vector<fs::path> entries_2{};

            std::copy(fs::recursive_directory_iterator{ path_1 }, {}, std::back_inserter(entries_1));
            std::copy(fs::recursive_directory_iterator{ path_2 }, {}, std::back_inserter(entries_2));

            std::sort(std::begin(entries_1), std::end(entries_1));
            std::sort(std::begin(entries_2), std::end(entries_2));

            return
                entries_1.size() == entries_2.size() and
                std::transform_reduce(std::begin(entries_1), std::end(entries_1), std::begin(entries_2),
                    true,
                    std::logical_and<>{},
                    [](auto& p1, auto& p2) { return are_filesystem_entries_equal(p1, p2); }
            );
        }
        return false;
    }
}  // namespace rtc::filesystem


#endif  // RTC_FILESYSTEM_H
