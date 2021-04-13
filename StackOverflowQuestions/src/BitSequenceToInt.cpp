#include <bitset>
#include <iostream>
#include <sstream>

void fill(const char* in, int* out)
{
    std::istringstream iss{ in };
    std::string temp_str{};
    std::bitset<32> bs{ 0 };
    while (iss >> temp_str)
    {
        size_t pos = static_cast<size_t>(std::stoi(temp_str, 0, 2));
        bs.set(pos);
    }
    //std::cout << bs.to_string() << "\n";
    *out = static_cast<int>(bs.to_ulong());
}

void bit_sequence_to_int_main()
{
    std::string in{ " 00101 10010 " };
    int out{ -1 };
    fill(in.c_str(), &out);
    std::cout << out << "\n";
}
