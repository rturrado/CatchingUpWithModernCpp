#include "Chapter9_DataSerialization.h"
#include "Chapter9_DataSerialization/pdf_writer_wrapper.h"

#include "AbstractContentContext.h"
#include "PageContentContext.h"
#include "PDFPage.h"
#include "PDFWriter.h"

#include <algorithm>  // any_of
#include <cctype>  // tolower
#include <filesystem>
#include <iostream>  // cout
#include <stdexcept>  // runtime_error
#include <utility>  // pair
#include <vector>


// Constants
//
// Page
const double page_width{ 595 };
const double page_height{ 842 };
// Margins
const double margin_left{ 20 };
const double margin_right{ 20 };
const double margin_top{ 30 };
const double margin_bottom{ 30 };
// Images
const double image_spacing{ 10 };


struct NotADirectoryError : public std::runtime_error
{
    NotADirectoryError(const std::string& path) : std::runtime_error{ message_ + path } {}
private:
    static inline std::string message_{ "not a directory: " };
};


void save_folder_of_images_to_pdf(const std::filesystem::path& input_dir_path, const std::filesystem::path& output_file_path)
{
    if (not std::filesystem::is_directory(input_dir_path))
    {
        throw NotADirectoryError(input_dir_path.string());
    }

    // PDF writer
    PDFWriter pdf_writer{};
    // Page
    PDFPage* page{};
    // Context
    PageContentContext* ctx{};
    // Cursor height
    double current_y{};

    auto start_page_and_page_content_context = [&pdf_writer, &page, &ctx, &current_y]() {
        if (not page) { page = rtc::pdf_writer::create_page(page_width, page_height); }
        if (not ctx) { ctx = rtc::pdf_writer::start_page_content_context(pdf_writer, page); };
    };
    auto end_page_and_page_content_context = [&pdf_writer, &page, &ctx]() {
        if (ctx) { rtc::pdf_writer::end_page_content_context(pdf_writer, ctx); ctx = nullptr; }
        if (page) { rtc::pdf_writer::write_page_and_release(pdf_writer, page); page = nullptr; }
    };

    rtc::pdf_writer::start_pdf(pdf_writer, output_file_path);
    start_page_and_page_content_context();
    current_y = page_height - margin_top;

    for (const auto& dir_entry : std::filesystem::directory_iterator{ input_dir_path })
    {
        auto is_image = [](const std::filesystem::path& path) {
            auto str_tolower = [](std::string s) {
                std::transform(std::begin(s), std::end(s), std::begin(s), [](unsigned char c) { return std::tolower(c); });
                return s;
            };
            const std::vector<std::string> valid_image_extensions{ ".jpg", ".jpeg", ".png", ".tiff" };
            auto extension{ str_tolower(path.extension().string()) };
            return std::any_of(std::cbegin(valid_image_extensions), std::cend(valid_image_extensions),
                [&extension](auto& s) { return s == extension; });
        };
        auto equals = [](double a, double b) {
            return (a - b < 0.1) and (b - a < 0.1);
        };
        auto less_than = [](double a, double b) {
            return (b - a > 0.1);
        };
        auto get_current_image_spacing = [&current_y, &equals]() {
            return equals(current_y, page_height - margin_top) ? 0 : image_spacing;
        };
        auto image_fits_in_current_page = [&current_y, &get_current_image_spacing, &less_than, &page](double image_height) {
            return less_than(image_height + get_current_image_spacing(), current_y - margin_bottom);
        };
        auto scale_image_to_fit_page = [&less_than](double image_width, double image_height)
        {
            auto ratio{ 1.0 };
            auto page_width_available{ page_width - margin_left - margin_right };
            auto page_height_available{ page_height - margin_top - margin_bottom };
            auto width_ratio{ image_width / page_width_available };
            auto height_ratio{ image_height / page_height_available };
            if (less_than(1.0, width_ratio) or less_than(1.0, height_ratio))
            {
                ratio = std::max(width_ratio, height_ratio);
            }
            return std::pair<double, double>{ image_width / ratio, image_height / ratio };
        };
        auto create_image_options_for_scaled_image = [](double scaled_image_width, double scaled_image_height) {
            AbstractContentContext::ImageOptions image_options{};
            image_options.transformationMethod = AbstractContentContext::eFit;
            image_options.boundingBoxWidth = scaled_image_width;
            image_options.boundingBoxHeight = scaled_image_height;
            image_options.fitProportional = true;
            return image_options;
        };

        if (not is_image(dir_entry.path())) { continue; }

        auto [image_width, image_height] = rtc::pdf_writer::get_image_dimensions(pdf_writer, dir_entry.path());
        auto [scaled_image_width, scaled_image_height] = scale_image_to_fit_page(image_width, image_height);
        if (not image_fits_in_current_page(scaled_image_height))
        {
            end_page_and_page_content_context();
            start_page_and_page_content_context();
            current_y = page_height - margin_top;
        }
        auto scaled_image_y{ current_y - scaled_image_height - get_current_image_spacing() };
        auto image_options{ create_image_options_for_scaled_image(scaled_image_width, scaled_image_height) };
        rtc::pdf_writer::draw_image(ctx, margin_left, scaled_image_y, dir_entry.path(), image_options);
        current_y = scaled_image_y;
    }

    end_page_and_page_content_context();
    rtc::pdf_writer::end_pdf(pdf_writer);
}

// Creating a PDF from a collection of images
//
// Write a program that can create a PDF document that contains images from a user-specified directory.
// The images must be displayed one after another.
// If an image does not fit on the remainder of a page, it must be placed on the next page.
void problem_78_main()
{
    const auto input_dir_path{ std::filesystem::current_path() /  "res/problem78/images" };
    const auto temp_file_path{ std::filesystem::temp_directory_path() / "images.pdf" };

    try
    {
        std::cout << "Writing PDF out to: " << temp_file_path << "\n\n";
        save_folder_of_images_to_pdf(input_dir_path, temp_file_path);
    }
    catch (const std::exception& err)
    {
        std::cout << "\"Error: " << err.what() << ".\"\n\n";
    }
}
