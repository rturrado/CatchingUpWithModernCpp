#include "Chapter10_ArchivesImagesAndDatabases.h"
#include "Chapter10_ArchivesImagesAndDatabases/png_writer_wrapper.h"

#include "RtcRandom.h"

#include <filesystem>
#include <format>
#include <iostream>  // cout

using namespace rtc::png_writer;

void paint_gradient_background(PNGWriter& png_writer)
{
    const int image_width{ png_writer.get_width() };
    const int image_height{ png_writer.get_height() };

    const Rectangle2D image_rectangle{ {1, 1}, {image_width, image_height} };
    const Gradient gradient{ { 0.3, 0.3, 0.7 }, {} };

    png_writer.plot_filled_rectangle_horizontal_gradient(image_rectangle, gradient);
}

void paint_random_letters(PNGWriter& png_writer)
{
    const int image_width{ png_writer.get_width() };
    const int image_height{ png_writer.get_height() };

    const auto font_file_root_path{ std::filesystem::current_path() / "res" / "fonts" };
    const std::vector<std::filesystem::path> font_file_names{
        "calibri.ttf",
        "calibrib.ttf",
        "calibrii.ttf",
        "calibril.ttf",
        "calibrili.ttf",
        "calibriz.ttf"
    };
    const auto number_of_letters{ 4 };

    RandomInt random_font{ 0, static_cast<int>(font_file_names.size()) - 1 };
    RandomInt random_font_size{ image_height / 4, image_height / 2 };
    RandomInt random_y{ image_height / 4, image_height / 2 };
    RandomInt random_angle{ 0, 45 };
    RandomLetter random_letter{};
    RandomFloatingPoint random_colour{ 0.4, 0.8 };

    for (int i{ 0 }; i < number_of_letters; ++i)
    {
        auto font_file_path{ font_file_root_path / font_file_names[random_font()] };
        auto font_size{ random_font_size() };
        auto start_position = Point2D{ i * image_width / number_of_letters, random_y()};
        auto angle{ (i % 2 == 0 ? -1.0 : 1.0) * random_angle() * 3.14 / 180 };
        auto text = std::string{ random_letter() };
        auto colour = RGB{ random_colour(), random_colour(), random_colour() };

        png_writer.plot_text(font_file_path, font_size, start_position, angle, text, colour);
    }
}

void paint_random_strokes(PNGWriter& png_writer)
{
    const int image_width{ png_writer.get_width() };
    const int image_height{ png_writer.get_height() };

    const auto number_of_strokes{ 8 };

    RandomInt random_x0{ 5 * image_width / 100, 10 * image_width / 100 };
    RandomInt random_x1{ 90 * image_width / 100, 95 * image_width / 100 };
    RandomInt random_y{ 5 * image_height / 100, 95 * image_height / 100 };
    RandomFloatingPoint random_colour{ 0.2, 0.6 };

    for (int i{ 0 }; i < number_of_strokes; ++i)
    {
        auto line = Line2D{ { random_x0(), random_y() }, { random_x1(), random_y() } };
        auto colour = RGB{ random_colour(), random_colour(), random_colour() };

        png_writer.plot_line(line, colour);
    }
}

// Creating verification text PNG images
//
// Write a program that can create Captcha-like PNG images for verifying human users to a system.
// Such an images should have:
//   - A gradient-coloured background.
//   - A series of random letters displayed at different angles both to the right and left.
//   - Several random lines of different colours accross the image (on top of the text).
void problem_83_main()
{
    const auto image_file_path{ create_png_file_path(std::filesystem::temp_directory_path(), "captcha") };

    std::cout << std::format("Creating {}...\n\n", image_file_path.string());

    PNGWriter png_writer(300, 200, 0.0, image_file_path);

    paint_gradient_background(png_writer);
    paint_random_letters(png_writer);
    paint_random_strokes(png_writer);
}
