#ifndef PDF_MOVIES_H
#define PDF_MOVIES_H

#include "Movies.h"
#include "pdf_writer_wrapper.h"

#include "AbstractContentContext.h"
#include "PageContentContext.h"
#include "PDFPage.h"
#include "PDFRectangle.h"
#include "PDFWriter.h"

#include <cmath>
#include <filesystem>
#include <iomanip>  // setfill, setw
#include <sstream>  // ostringstream


namespace rtc::movies::pdf
{
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
    // Text
    const double font_width{ 8 };
    const double font_height{ 14 };
    const double line_spacing{ 5 };

    // doc
    struct doc
    {
        Catalog catalog{};

        doc() = default;
        doc(const Catalog& c) : catalog{ c } {}

        inline void save_as_table(const std::filesystem::path& output_file_path)
        {
            using namespace PDFHummus;

            auto start_pdf = [](auto& pdf_writer, auto& output_file_path) {
                auto output_file_path_str{ output_file_path.string() };
                if (pdf_writer.StartPDF(output_file_path_str, ePDFVersion17) != eSuccess)
                {
                    throw rtc::pdf_writer::StartPdfError{ output_file_path_str };
                }
            };
            auto end_pdf = [](auto& pdf_writer) {
                if (pdf_writer.EndPDF() != eSuccess)
                {
                    throw rtc::pdf_writer::EndPdfError{ pdf_writer.GetOutputFile().GetFilePath() };
                }
            };
            auto create_page = []() {
                auto page{ new PDFPage{} };
                page->SetMediaBox(PDFRectangle{ 0, 0, page_width, page_height });
                return page;
            };
            auto write_page_and_release = [](auto& pdf_writer, auto page) {
                if (pdf_writer.WritePageAndRelease(page) != eSuccess)
                {
                    throw rtc::pdf_writer::WritePageAndRelease{ pdf_writer.GetOutputFile().GetFilePath() };
                };
            };
            auto start_page_content_context = [](auto& pdf_writer, auto page) {
                return pdf_writer.StartPageContentContext(page);
            };
            auto end_page_content_context = [](auto& pdf_writer, auto ctx) {
                if (pdf_writer.EndPageContentContext(ctx) != eSuccess)
                {
                    throw rtc::pdf_writer::EndPageContentContextError{ pdf_writer.GetOutputFile().GetFilePath() };
                }
            };
            auto write_text = [](auto ctx, auto x, auto y, auto text, auto text_options) {
                ctx->WriteText(x, y, text, text_options);
            };
            auto draw_line = [](auto ctx, auto x1, auto y1, auto x2, auto y2) {
                ctx->DrawPath({ {x1, y1}, {x2, y2} });
            };

            // PDF writer
            PDFWriter pdf_writer{};
            start_pdf(pdf_writer, output_file_path);

            // Font, text options
            const auto font{ pdf_writer.GetFontForFile(R"(C:\Windows\Fonts\Pala.ttf)") };
            const AbstractContentContext::TextOptions text_options{ font, font_height, AbstractContentContext::eGray, 0 };

            // Movies
            for (auto it{ std::cbegin(catalog.movies) }; it != std::cend(catalog.movies); )
            {
                // Page
                auto page{ create_page() };

                // Context
                auto ctx{ start_page_content_context(pdf_writer, page) };

                // Cursor height
                double current_y{ page_height - margin_top };

                // Title (only in the first page)
                if (it == std::cbegin(catalog.movies))
                {
                    current_y -= font_height;
                    write_text(ctx, margin_left + font_width, current_y, "List of movies", text_options);
                }

                // Line separator
                current_y -= (line_spacing);
                draw_line(ctx, margin_left, current_y, page_width - margin_right, current_y);

                // Page layout
                const size_t movies_per_page{ 25 };

                // Movies per page
                auto page_it_end{ it + std::min(static_cast<size_t>(std::distance(it, std::cend(catalog.movies))), movies_per_page) };
                for (; it != page_it_end; ++it)
                {
                    auto movie_year_to_string = [](auto year) {
                        return std::string{ "(" } + std::to_string(static_cast<int>(year)) + ")";
                    };
                    auto movie_length_to_string = [](auto length) {
                        std::ostringstream oss{};
                        oss << length / 60 << ":" << std::setw(2) << std::setfill('0') << length % 60;
                        return oss.str();
                    };

                    auto& movie{ *it };
                    std::string movie_year{ movie_year_to_string(movie.year) };
                    std::string movie_length{ movie_length_to_string(movie.length) };

                    std::ostringstream oss{};
                    oss << movie.title << " " << movie_year;
                    
                    // Movie
                    current_y -= (font_height + line_spacing);
                    write_text(ctx, margin_left + font_width, current_y, oss.str(), text_options);
                    write_text(ctx, page_width - margin_right - font_width * movie_length.size(), current_y, movie_length, text_options);
                }

                // Line separator
                current_y -= (line_spacing);
                draw_line(ctx, margin_left, current_y, page_width - margin_right, current_y);

                end_page_content_context(pdf_writer, ctx);
                write_page_and_release(pdf_writer, page);
            }

            end_pdf(pdf_writer);
        }
    };
}  // namespace rtc::movies::pdf


#endif  // PDF_MOVIES_H
