#ifndef PDF_WRITER_WRAPPER_H
#define PDF_WRITER_WRAPPER_H

#include "AbstractContentContext.h"
#include "PageContentContext.h"
#include "PDFPage.h"
#include "PDFRectangle.h"
#include "PDFWriter.h"

#include <filesystem>
#include <stdexcept>  // runtime_error
#include <string>

namespace rtc::pdf_writer
{
    using TextOptions = AbstractContentContext::TextOptions;
    using ImageOptions = AbstractContentContext::ImageOptions;

    // Runtime errors
    struct StartPdfError : public std::runtime_error
    {
        StartPdfError(const std::string& path) : std::runtime_error{ message_ + path } {}
    private:
        static inline std::string message_{ "trying to start PDF: " };
    };
    struct EndPdfError : public std::runtime_error
    {
        EndPdfError(const std::string& path) : std::runtime_error{ message_ + path } {}
    private:
        static inline std::string message_{ "trying to end PDF: " };
    };
    struct EndPageContentContextError : public std::runtime_error
    {
        EndPageContentContextError(const std::string& path) : std::runtime_error{ message_ + path } {}
    private:
        static inline std::string message_{ "trying to end page content context: " };
    };
    struct WritePageAndRelease : public std::runtime_error
    {
        WritePageAndRelease(const std::string& path) : std::runtime_error{ message_ + path } {}
    private:
        static inline std::string message_{ "trying to write page and release: " };
    };


    // PDF writer function wrappers
    inline auto start_pdf(PDFWriter& pdf_writer, const std::filesystem::path& output_file_path)
    {
        auto output_file_path_str{ output_file_path.string() };
        if (pdf_writer.StartPDF(output_file_path_str, ePDFVersion17) != eSuccess)
        {
            throw rtc::pdf_writer::StartPdfError{ output_file_path_str };
        }
    }
    inline auto end_pdf(PDFWriter& pdf_writer)
    {
        if (pdf_writer.EndPDF() != eSuccess)
        {
            throw rtc::pdf_writer::EndPdfError{ pdf_writer.GetOutputFile().GetFilePath() };
        }
    }
    inline auto create_page(double width, double height)
    {
        auto page{ new PDFPage{} };
        page->SetMediaBox(PDFRectangle{ 0, 0, width, height });
        return page;
    }
    inline auto write_page_and_release(PDFWriter& pdf_writer, PDFPage* page)
    {
        if (pdf_writer.WritePageAndRelease(page) != eSuccess)
        {
            throw rtc::pdf_writer::WritePageAndRelease{ pdf_writer.GetOutputFile().GetFilePath() };
        };
    }
    inline auto start_page_content_context(PDFWriter& pdf_writer, PDFPage* page)
    {
        return pdf_writer.StartPageContentContext(page);
    }
    inline auto end_page_content_context(PDFWriter& pdf_writer, PageContentContext* ctx)
    {
        if (pdf_writer.EndPageContentContext(ctx) != eSuccess)
        {
            throw rtc::pdf_writer::EndPageContentContextError{ pdf_writer.GetOutputFile().GetFilePath() };
        }
    }
    inline auto write_text(PageContentContext* ctx, double x, double y, const std::string& text, const TextOptions& text_options)
    {
        ctx->WriteText(x, y, text, text_options);
    }
    inline auto draw_line(PageContentContext* ctx, double x1, double y1, double x2, double y2)
    {
        ctx->DrawPath({ {x1, y1}, {x2, y2} });
    }
    inline auto get_image_dimensions(PDFWriter& pdf_writer, const std::filesystem::path& image_file_path)
    {
        return pdf_writer.GetImageDimensions(image_file_path.string());
    }
    inline auto draw_image(PageContentContext* ctx, double x, double y, const std::filesystem::path& image_file_path, const ImageOptions& image_options = ImageOptions{})
    {
        ctx->DrawImage(x, y, image_file_path.string(), image_options);
    }
}  // rtc::pdf_writer

#endif  // PDF_WRITER_WRAPPER_H
