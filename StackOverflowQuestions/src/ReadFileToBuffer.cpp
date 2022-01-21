#include <filesystem>
#include <format>
#include <fstream>  // ifstream
#include <iostream>  // cout
#include <vector>

namespace fs = std::filesystem;

void read_file_to_buffer_main()
{
    fs::path file_path{ fs::current_path() / "res" / "file.ini" };
    std::ifstream ifs{ file_path, std::ios::in | std::ios::binary };
    std::vector<char> buffer{ std::istreambuf_iterator<char>{ifs}, {} };
    std::cout << std::format("Read {} bytes.\n", buffer.size());
}
