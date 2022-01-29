#include "Chapter10_ArchivesImagesAndDatabases.h"
#include "Chapter10_ArchivesImagesAndDatabases/png_writer_wrapper.h"
#include "Chapter10_ArchivesImagesAndDatabases/ean_13_barcode.h"

#include <filesystem>
#include <format>
#include <iostream>  // cout
#include <string>

using namespace rtc::png_writer;

void paint_bar(PNGWriter& png_writer, const Point2D bottom_left_position, int width, int height)
{
    png_writer.fill_rectangle(
        Rectangle2D{
            .bottom_left = { bottom_left_position.x, bottom_left_position.y },
            .top_right = { bottom_left_position.x + width - 1, bottom_left_position.y + height - 1 } },
        RGB{}
    );
}

template <size_t N>
Point2D paint_bitset(PNGWriter& png_writer, const std::bitset<N>& bs, Point2D bottom_left_position, int width, int height)
{
    for (int i{ static_cast<int>(bs.size()) - 1 }; i >= 0; i--)
    {
        if (bs[i])
        {
            paint_bar(png_writer, bottom_left_position, width, height);
        }
        bottom_left_position.x += width;
    }
    return bottom_left_position;
}

void paint_ean_13_barcode(PNGWriter& png_writer, const ean_13_barcode& code)
{
    int image_width{ png_writer.get_width() };
    int image_height{ png_writer.get_height() };

    Rectangle2D bounding_box{
        { 5 * image_width / 100, 5 * image_height / 100 },
        { 95 * image_width / 100, 95 * image_height / 100 }
    };

    int marker_bar_height{ bounding_box.get_height() };
    int digit_bar_height{ 95 * marker_bar_height / 100 };
    int bar_height_difference{ marker_bar_height - digit_bar_height };

    int number_of_bar_areas{ 95 };
    int bar_area_width{ bounding_box.get_width() / number_of_bar_areas };

    Point2D bar_bottom_left_position{ bounding_box.bottom_left };

    // Start marker
    bar_bottom_left_position = paint_bitset(png_writer, code.get_start_marker(), bar_bottom_left_position, bar_area_width, marker_bar_height);

    // First group
    bar_bottom_left_position.y += bar_height_difference;
    for (const auto& digit_bs : code.get_first_group_bs())
    {
        bar_bottom_left_position = paint_bitset(png_writer, digit_bs, bar_bottom_left_position, bar_area_width, digit_bar_height);
    }

    // Center marker
    bar_bottom_left_position.y -= bar_height_difference;
    bar_bottom_left_position = paint_bitset(png_writer, code.get_center_marker(), bar_bottom_left_position, bar_area_width, marker_bar_height);

    // Second group
    bar_bottom_left_position.y += bar_height_difference;
    for (const auto& digit_bs : code.get_second_group_bs())
    {
        bar_bottom_left_position = paint_bitset(png_writer, digit_bs, bar_bottom_left_position, bar_area_width, digit_bar_height);
    }

    // End marker
    bar_bottom_left_position.y -= bar_height_difference;
    bar_bottom_left_position = paint_bitset(png_writer, code.get_end_marker(), bar_bottom_left_position, bar_area_width, marker_bar_height);
}

// EAN-13 barcode generator
//
// Write a program that can generate a PNG image with an EAN-13 barcode for any international article number in version 13 of the standard.
// For simplicity, the image should only contain the barcode and can skip the EAN-13 number printed under the barcode.
void problem_84_main()
{
    for (auto&& code_str : { "2407014001944", "9781123123456", "5012345678900" })
    {
        const auto image_file_path{ create_png_file_path(std::filesystem::temp_directory_path(), code_str) };
        const auto code{ ean_13_barcode{ code_str } };

        std::cout << std::format("Creating {}...\n\n", image_file_path.string());

        PNGWriter png_writer(300, 200, 1.0, image_file_path);

        paint_ean_13_barcode(png_writer, code);
    }
}
