#include <exception>
#include <iostream>

#include "Filesystem.h"
#include "RAIIDemo.h"
#include "VariadicTemplates.h"

int main()
{
    // Variadic templates
    {
        std::cout << "[VARIADIC TEMPLATES]\n";
        std::cout << "Sum of { 23, 5, 1977 } = " << summer(23, 5, 1977) << "\n";
        std::cout << "\n";
    }

    // Filesystem
    {
        std::cout << "[FILESYSTEM]\n";
        filesystem_main();
        std::cout << "\n";
    }

    // RAII demo
    {
        std::cout << "[RAII DEMO]\n";
        try
        {
            raii_demo_main();
        }
        catch (const std::exception& err)
        {
            std::cout << "Error: " << err.what() << "\n";
        }
        std::cout << "\n";
    }
}
