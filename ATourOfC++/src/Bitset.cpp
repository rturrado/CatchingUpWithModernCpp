#include "Bitset.h"

#include <bitset>
#include <cassert>
#include <iostream>

// byte_index 0 is the most significative byte
template <int N>
std::bitset<8> extract_byte(std::bitset<N> bs, size_t byte_index)
{
    size_t size_in_bytes = N / 8;
    assert(byte_index <= (size_in_bytes - 1));
    bs <<= byte_index * 8;  // zero bytes to the left of the index
    bs >>= (size_in_bytes - 1) * 8;  // zero bytes to the right of the index
                                     // and leave indexed byte at the least significative byte
    return std::bitset<8>(bs.to_ulong());
}

template <int N>
void print_bitset(const std::bitset<N>& bs)
{
    std::cout << "Binary: 0b" << bs << "\n";
    std::cout << "Hex: 0x" << std::hex << bs.to_ulong() << "\n";
    std::cout << "Char: ";

    size_t size_in_bytes = N / 8; 
    for (size_t byte_index = 0; byte_index < size_in_bytes; ++byte_index)
    {
        std::bitset<8> bs8 = extract_byte(bs, byte_index);
        if (bs8.any())
        {
            std::cout << static_cast<char>(bs8.to_ulong());
        }
    }
    std::cout << "\n\n";
}

void bitset_main()
{
    std::bitset<8> bs1{ 'a' };  // 0b0110'0001
    print_bitset(bs1);

    std::bitset<8> bs2{ bs1 |= 128 };  // 0b1110'0001
    print_bitset(bs2);

    std::bitset<32> bs3{ ('a' << 24) | ('b' << 16) | ('c' << 8) | 'd' };
    print_bitset(bs3);
}
