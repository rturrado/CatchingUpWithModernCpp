#ifndef PNG_WRITER_WRAPPER_H
#define PNG_WRITER_WRAPPER_H

#include "pngwriter.h"

#include <filesystem>
#include <string>


namespace rtc::png_writer
{
    namespace fs = std::filesystem;

    const fs::path png_file_extension{ "png" };

    inline auto create_png_file_path(const fs::path& file_root_path, const std::string& file_stem)
    {
        auto file_path{ file_root_path / file_stem };
        file_path.replace_extension(png_file_extension);
        return file_path;
    };

    struct RGB {
        double r{};
        double g{};
        double b{};
    };

    struct Point2D {
        int x{};
        int y{};
    };

    struct Line2D {
        Point2D from{};
        Point2D to{};
    };

    struct Rectangle2D {
        Point2D top_left{};
        Point2D bottom_right{};
    };

    struct Gradient {
        RGB start{};
        RGB end{};
    };

    class PNGWriter {
    public:
        PNGWriter(int w, int h, double bc, const fs::path& fp) : writer{ w, h, bc, fp.string().c_str() } {}
        ~PNGWriter() { writer.close(); }

        void fill_rectangle(const Rectangle2D& rectangle, const RGB& colour)
        {
            writer.filledsquare(rectangle.top_left.x, rectangle.top_left.y, rectangle.bottom_right.x, rectangle.bottom_right.y,
                colour.r, colour.g, colour.b);
        }

        void fill_rectangle_horizontal_gradient(const Rectangle2D& rectangle, const Gradient& gradient)
        {
            const auto width{ rectangle.bottom_right.x - rectangle.top_left.x };
            const auto y0{ rectangle.top_left.y };
            const auto y1{ rectangle.bottom_right.y };

            for (int x{rectangle.top_left.x}; x <= rectangle.bottom_right.x; ++x)
            {
                auto factor{ static_cast<double>(x) / width };
                auto red{ (gradient.end.r - gradient.start.r) * factor + gradient.start.r };
                auto green{ (gradient.end.g - gradient.start.g) * factor + gradient.start.g };
                auto blue{ (gradient.end.b - gradient.start.b) * factor + gradient.start.b };
                writer.line(x, y0, x, y1, red, green, blue);
            }
        }

        void line(const Line2D& line, const RGB& colour)
        {
            writer.line(line.from.x, line.from.y, line.to.x, line.to.y, colour.r, colour.g, colour.b);
        }

        void plot_text(
            fs::path font_file_path,
            int font_size,
            const Point2D& bottom_left_position,
            double angle,
            std::string text,
            const RGB& colour)
        {
            writer.plot_text(
                const_cast<char*>(font_file_path.string().c_str()),
                font_size,
                bottom_left_position.x, bottom_left_position.y,
                angle,
                const_cast<char*>(text.c_str()),
                colour.r, colour.g, colour.b);
        }
    private:
        pngwriter writer{};
    };
}  // namespace rtc::png_writer


#endif  // PNG_WRITER_WRAPPER_H
