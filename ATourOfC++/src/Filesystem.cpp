#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "Filesystem.h"

using namespace std::filesystem;

void print_directory(std::filesystem::path p)
{
    try {
        if (is_directory(p))
        {
            std::cout << p << ":\n";
            for (const directory_entry& x : directory_iterator{ p })
            {
                std::cout << "\t" << x.path() << '\n';
            }
        }
        else
        {
            std::cout << "Error: " << p << " is not a directory\n";
        }
    }
    catch (const std::filesystem::filesystem_error& ex)
    {
        std::cerr << ex.what() << '\n';
    }
}

void filesystem_main()
{
    print_directory(".");  // Current directory
    print_directory("..");  // Parent directory
    print_directory("/");  // Unix root directory
    print_directory("c:");  // Windows volume C
    std::cout << "Please input a directory path ('quit' to finish): ";
    for (std::string s; std::cin >> s; )
    {
        if (s == "quit")
        {
            break;
        }
        print_directory(s);
        std::cout << "Please input a directory path ('quit' to finish): ";
    }
}
