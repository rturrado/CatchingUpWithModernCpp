#ifndef PNG_WRITER_WRAPPER_H
#define PNG_WRITER_WRAPPER_H

#include "pngwriter.h"

#include <filesystem>
#include <string>


namespace rtc::png_writer
{
    namespace fs = std::filesystem;

    const fs::path png_file_extension{ "png" };

    auto create_png_file_path(const fs::path& file_root_path, const std::string& file_stem)
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

    struct Rectangle2D {
        Point2D top_left{};
        Point2D bottom_right{};
    };

    class PNGWriter {
    public:
        PNGWriter(int w, int h, double bc, const fs::path& fp) : writer{ w, h, bc, fp.string().c_str() } {}
        ~PNGWriter() { writer.close(); }

        void fill_rectangle(const Rectangle2D& r, const RGB& c)
        {
            writer.filledsquare(r.top_left.x, r.top_left.y, r.bottom_right.x, r.bottom_right.y, c.r, c.g, c.b);
        }
    private:
        pngwriter writer{};
    };
}  // namespace rtc::png_writer


#endif  // PNG_WRITER_WRAPPER_H

