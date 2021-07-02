#include "Chapter2_LanguageFeatures.h"
#include "Array2D.h"

#include <algorithm>
#include <exception>
#include <iostream>
#include <numeric>

// Creating a 2D array with basic operations
// Write a class template that represents a two-dimensional array container with methods for
// element access (at() and data()), capacity querying, iterators, filling, and swapping.
// It should be possible to move objects of this type.
void problem_17_main()
{
    try
    {
        // Array of ints initialized with width and height
        // Then modified using iota()
        Array2D<int> arr1(3, 3);
        std::iota(arr1.begin(), arr1.end(), 1);
        arr1.print();

        // Array of floats initialized with width and height
        // Then modified using at()
        Array2D<float> arr2(3, 3);
        float f{ static_cast<float>(2.37) };
        for (auto row = 0; row < arr2.height(); ++row)
        {
            for (auto col = 0; col < arr2.width(); ++col)
            {
                arr2.at(row, col) = f;
                f *= 2;
            }
        }
        arr2.print();

        // Array initialized with a initializer list of initializer lists
        Array2D<std::string> arr3{
            { "En", "un", "lugar", "de" },
            { "la", "Mancha", "de", "cuyo" },
            { "nombre", "no", "quiero", "acordarme" },
            { "no", "ha", "mucho", "que" }
        };
        arr3.print(10);

        // Array initialized with move constructor
        auto arr4{ std::move(arr2) };
        arr4.print();

        // Array initialized with copy constructor
        // Then modified using transform()
        // transform() uses difference_type operator-()
        auto arr5{ arr1 };
        std::transform(arr1.cbegin(), arr1.cend(), arr5.begin(), [](auto n) { return n + 1; });
        arr5.print();

        // Swapping of elements
        arr5.swap(0, 0, 2, 2);
        arr5.print();

        // Sub arrays
        auto arr6{ arr3.sub_array(1, 1, 1, 2) };
        arr6.print();

        // Rows and columns as vectors
        auto row1{ arr3.row_as_vector(2) };
        print(row1);
        auto col1{ arr3.column_as_vector(3) };
        print(col1);

        // Reverse iterators
        std::transform(arr1.crbegin(), arr1.crend(), arr5.begin(), [](auto n) { return n + 1; });
        arr5.print();

        // Test out of range access
        arr5.swap(3, 0, 2, 2);
        arr5.print();
    }
    catch (const std::exception& err)
    {
        std::cout << "Error: " << err.what() << "\n\n";
    }
}
