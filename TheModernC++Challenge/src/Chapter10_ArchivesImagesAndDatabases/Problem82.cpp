#include "Chapter10_ArchivesImagesAndDatabases.h"
#include "Chapter10_ArchivesImagesAndDatabases/png_writer_wrapper.h"

#include <iostream>  // cout
#include <filesystem>
#include <format>

// Creating a PNG that represents a national flag
//
// Write a program that generates a PNG file that represents the national flag of Romania.
// The size of the image in pixels, as well as the path to the destination file, should be provided by the user.
void problem_82_main()
{
    namespace fs = std::filesystem;

    using namespace rtc::png_writer;

    constexpr const int image_width{ 300 };
    constexpr const int image_height{ 200 };
    constexpr const double background_colour{};
    const fs::path image_file_path{ create_png_file_path(fs::temp_directory_path(), "romania_flag") };

    std::cout << std::format("Creating {}...\n\n", image_file_path.string());

    PNGWriter png_writer(image_width, image_height, background_colour, image_file_path);

    constexpr const int strip_width{ image_width / 3 };

    constexpr const Rectangle2D blue_stripe{ { 1, 1 }, { strip_width, image_height } };
    constexpr const Rectangle2D yellow_stripe{ { strip_width + 1, 1 }, { strip_width * 2, image_height } };
    constexpr const Rectangle2D red_stripe{ { strip_width * 2 + 1, 1 }, { image_width, image_height } };

    constexpr const RGB romanian_flag_blue{ 0.0, 43.0 / 255, 127.0 / 255 };  // Pantone 280c
    constexpr const RGB romanian_flag_yellow{ 252.0 / 255, 209.0 / 255, 22.0 / 255 };  // Pantone 116c
    constexpr const RGB romanian_flag_red{ 206.0 / 255, 17.0 / 255, 38.0 / 255 };  // Pantone 186c

    png_writer.fill_rectangle(blue_stripe, romanian_flag_blue);
    png_writer.fill_rectangle(yellow_stripe, romanian_flag_yellow);
    png_writer.fill_rectangle(red_stripe, romanian_flag_red);
}
