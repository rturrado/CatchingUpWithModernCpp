#ifndef PDF_WRITER_WRAPPER_H
#define PDF_WRITER_WRAPPER_H

#include "AbstractContentContext.h"
#include "PageContentContext.h"
#include "PDFPage.h"
#include "PDFRectangle.h"
#include "PDFWriter.h"

#include <stdexcept>  // runtime_error
#include <string>

namespace rtc::pdf_writer
{
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
}  // rtc::pdf_writer

#endif  // PDF_WRITER_WRAPPER_H
