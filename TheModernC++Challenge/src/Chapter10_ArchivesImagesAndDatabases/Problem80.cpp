#include "Chapter10_ArchivesImagesAndDatabases.h"
#include "ConsoleRead.h"

#include "ZipArchive.h"
#include "ZipArchiveEntry.h"
#include "ZipFile.h"

#include <algorithm>  // copy, sort
#include <cstdint>  // uint8_t
#include <filesystem>
#include <format>
#include <functional>  // logical_and
#include <fstream>  // ifstream
#include <iostream>  // cout
#include <iterator>  // back_inserter, istreambuf_iterator
#include <numeric>  // transform_reduce
#include <stdexcept>  // runtime_error
#include <string>
#include <vector>

namespace fs = std::filesystem;

const fs::path zip_file_extension{ "zip" };

struct FilePathDoesNotExistError : public std::runtime_error
{
    FilePathDoesNotExistError(const std::string& path) : std::runtime_error{ message_ + path } {}
private:
    static inline std::string message_{ "file path does not exist: " };
};

bool are_filesystem_entries_equal(const fs::path& path_1, const fs::path& path_2)
{
    if (path_1.filename() != path_2.filename()) { return false; }

    std::ifstream ifs_1{ path_1, std::ios::in | std::ios::binary };
    std::ifstream ifs_2{ path_2, std::ios::in | std::ios::binary };
    std::vector<uint8_t> contents_1{ std::istreambuf_iterator{ifs_1}, {} };
    std::vector<uint8_t> contents_2{ std::istreambuf_iterator{ifs_2}, {} };
    return contents_1 == contents_2;
}

bool are_filesystem_trees_equal(const fs::path& path_1, const fs::path& path_2)
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

void create_directories_if_needed(const fs::path& path)
{
    if (not fs::exists(path))
    {
        fs::create_directories(path);
    }
};

void add_file_to_archive(const fs::path& input_path, const fs::path& zip_file_path)
{
    ZipFile::AddFile(zip_file_path.string(), input_path.string(), input_path.string());
}

void add_directory_to_archive(const fs::path& input_path, const fs::path& zip_file_path)
{
    auto archive{ ZipFile::Open(zip_file_path.generic_string()) };
    auto entry{ archive->CreateEntry(input_path.generic_string()) };
    entry->SetAttributes(ZipArchiveEntry::Attributes::Directory);
    ZipFile::SaveAndClose(archive, zip_file_path.generic_string());
}

void add_entry_to_archive(const fs::path& input_path, const fs::path& zip_file_path)
{
    if (fs::is_regular_file(input_path)) { add_file_to_archive(input_path, zip_file_path); }
    else if (fs::is_directory(input_path)) { add_directory_to_archive(input_path, zip_file_path); }
}

void compress(const fs::path& input_path, const fs::path& zip_file_path)
{
    std::cout << std::format("Compressing: {} -> {}\n", input_path.generic_string(), zip_file_path.generic_string());
    if (not fs::exists(input_path)) { throw FilePathDoesNotExistError{ input_path.generic_string()}; }
    if (fs::exists(zip_file_path)) { fs::remove(zip_file_path); }

    try
    {
        if (fs::is_regular_file(input_path))
        {
            std::cout << std::format("\tAdding entry: {}\n", input_path.generic_string());
            add_entry_to_archive(input_path, zip_file_path);
        }
        else if (fs::is_directory(input_path))
        {
            for (auto& directory_entry : fs::recursive_directory_iterator{ input_path })
            {
                std::cout << std::format("\tAdding entry: {}\n", directory_entry.path().generic_string());
                add_entry_to_archive(directory_entry.path(), zip_file_path);
            }
        }
    }
    catch (const std::exception&)
    {
        std::cout << std::format("\tRemoving archive file: {}\n", zip_file_path.generic_string());
        if (fs::exists(zip_file_path)) { fs::remove(zip_file_path); }
        throw;
    }
}

void decompress(const fs::path& zip_file_path, const fs::path& output_root_path)
{
    std::cout << std::format("Decompressing: {} -> {}\n", zip_file_path.generic_string(), output_root_path.generic_string());
    if (not fs::exists(zip_file_path)) { throw FilePathDoesNotExistError{ zip_file_path.generic_string() }; }
    if (not fs::exists(output_root_path)) { throw FilePathDoesNotExistError{ output_root_path.generic_string() }; }

    std::cout << std::format("\tOpening archive file: {}\n", zip_file_path.generic_string());
    auto archive{ ZipFile::Open(zip_file_path.generic_string()) };

    for (auto i{ 0 }; i < archive->GetEntriesCount(); ++i)
    {
        auto entry{ archive->GetEntry(i) };

        fs::path entry_file_path{ entry->GetFullName() };
        fs::path entry_relative_file_path{ entry_file_path.relative_path() };
        fs::path destination_file_path{ output_root_path / entry_relative_file_path };

        if (not entry->IsDirectory())
        {
            create_directories_if_needed(destination_file_path.parent_path());

            std::cout << std::format("\tExtracting: {}\n", destination_file_path.generic_string());
            ZipFile::ExtractFile(zip_file_path.generic_string(), entry_file_path.generic_string(), destination_file_path.generic_string());
        }
    }
}

void compare_input_and_output_paths(const fs::path& input_path, const fs::path& output_path)
{
    std::cout << std::format("Checking input '{}' and output '{}' are equal\n", input_path.generic_string(), output_path.generic_string());
    if (not are_filesystem_trees_equal(input_path, output_path))
    {
        std::cout << std::format("\tError: Input '{}' is different than output '{}'\n", input_path.generic_string(), output_path.generic_string());
    }
    else
    {
        std::cout << "\tOK\n";
    }
}

void remove_output_path(const fs::path& path)
{
    auto c{
        read_char(
            std::format("Are you sure you want to remove '{}' and all its contents? [y/n] ", path.string()),
            std::vector<char>{'n', 'N', 'y', 'Y'})
    };
    if (c == 'y' or c == 'Y')
    {
        fs::remove_all(path);
    }
}

// Compressing and decompressing files to/from a ZIP archive
//
// Write a program that can do the following:
//   - Compress either a file or the contents of a user-specified directory, recursively, to a ZIP archive.
//   - Decompress the contents of a ZIP archive to a user-specified destination directory.
void problem_80_main()
{
    auto create_zip_file_path = [](const fs::path& output_root_path, const fs::path& input_path)
    {
        auto zip_file_name{ input_path.filename() };
        zip_file_name.replace_extension(zip_file_extension);
        return output_root_path / zip_file_name;
    };

    const auto input_file_path{ fs::path{ "res" } / "problem80" / "file.jpg" };  // test absolute paths
    const auto input_dir_path{ fs::current_path() / "res" / "problem80" / "folder" };  // and relative paths
    const auto output_root_path{ fs::temp_directory_path() };

    for (auto&& input_path : { input_file_path, input_dir_path })
    {
        const auto zip_file_path{ create_zip_file_path(output_root_path, input_path) };
        const auto output_path{ output_root_path / input_path.relative_path() };
        const auto output_relative_root_directory_path{ output_root_path / *input_path.relative_path().begin() };
        try
        {
            compress(input_path, zip_file_path);
            decompress(zip_file_path, output_root_path);
            compare_input_and_output_paths(input_path, output_path);
            remove_output_path(output_relative_root_directory_path);
        }
        catch (const std::exception& ex)
        {
            std::cout << std::format("\nError: {}\n", ex.what());
        }
        std::cout << "\n";
    }
}
