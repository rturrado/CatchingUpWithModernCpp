#include "Chapter2_LanguageFeatures.h"
#include "UniqueHdl.h"

#include <cassert>
#include <iostream>
#include <filesystem>
#include <vector>
#include <stdexcept>

void function_that_throws() { throw std::runtime_error{"I'm a throwing function!\n"}; }

// System handle wrapper
// Consider an operating system handle, such as a file handle.
// Write a wrapper that handles the acquisition and release of the handle,
// as well as other operations such as verifying the validity of the handle
// and moving handle ownership from one object to another.
void test_unique_hdl()
{
    auto file_path{ std::filesystem::current_path().wstring() + L"./res./sample.txt" };

    unique_hdl file_hdl{
        file_path.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    };

    if (!file_hdl)
    {
        std::wcout << L"Error " << GetLastError() << ": in unique_hdl constructor\n";
        return;
    }

    auto another_file_hdl{ std::move(file_hdl) };
    assert(another_file_hdl);

    std::vector<char> buffer(1024);
    DWORD bytesRead = 0;
    if (!ReadFile(
            another_file_hdl.get(),
            buffer.data(),
            static_cast<DWORD>(buffer.size()),
            &bytesRead,
            nullptr)
        )
    {
        std::cout << "Error " << GetLastError() << ": in ReadFile\n";
    }

    function_that_throws();
}

void problem_21_main()
{
    try
    {
        test_unique_hdl();
    }
    catch (const std::runtime_error& ex)
    {
        std::cout << "Error: " << ex.what();
    }
}
