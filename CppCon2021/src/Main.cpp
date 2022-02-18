#include <iostream>  // cout

#include "RangesTest.h"

import Composition;
import InfiniteSequence;

int main()
{
    // Composition
    { std::cout << "[COMPOSITION]\n"; composition_main(); std::cout << "\n"; }
    // Infinite sequence
    { std::cout << "[INFINITE SEQUENCE]\n"; infinite_sequence_main(); std::cout << "\n"; }
    // Ranges
    { std::cout << "[RANGES]\n"; ranges_test_main(); std::cout << "\n"; }
}
