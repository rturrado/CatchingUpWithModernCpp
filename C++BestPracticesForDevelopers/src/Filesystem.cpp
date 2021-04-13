#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "Filesystem.h"

using namespace std::filesystem;

void filesystem_main()
{
    std::cout << "Creating count.txt\n";
    path path{ "count.txt" };
    std::ofstream of{ path };
    for (int i = 1; i <= 10; i++)
    {
        of << i << "\n";
    }
    of.close();
}
