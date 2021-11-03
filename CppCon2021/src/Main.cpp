#include <iostream>  // cout

import Composition;
import InfiniteSequence;
import Ranges;

int main()
{
    // Composition
    { std::cout << "[COMPOSITION]\n"; composition_main(); std::cout << "\n\n"; }
    // Infinite sequence
    { std::cout << "[INFINITE SEQUENCE]\n"; infinite_sequence_main(); std::cout << "\n\n"; }
    // Ranges
    { std::cout << "[RANGES]\n"; ranges_main(); std::cout << "\n\n"; }
}
