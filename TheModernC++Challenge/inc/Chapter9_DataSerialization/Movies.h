#ifndef MOVIES_H
#define MOVIES_H

#include "PrettyPrint.h"

#include <chrono>
#include <filesystem>
#include <optional>
#include <ostream>
#include <string>
#include <vector>


namespace rtc::movies
{
    namespace fs = std::filesystem;

    struct Role
    {
        std::string star{};
        std::string name{};

        void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept
        {
            os << fill_line_start << star << " (" << name << ")";
        }
        auto operator<=>(const Role& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const Role& role) { role.print(os); return os; }

    struct Cast
    {
        std::vector<Role> cast{};

        void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept
        {
            os << fill_line_start << "Cast:\n";
            for (const auto& role : cast)
            {
                role.print(os, fill_line_start + 1); os << "\n";
            }
        }
        auto operator<=>(const Cast& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const Cast& cast) { cast.print(os); return os; }

    struct Director
    {
        std::string name{};

        void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept
        {
            os << fill_line_start << name;
        }
        auto operator<=>(const Director& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const Director& director) { director.print(os); return os; }

    struct Directors
    {
        std::vector<Director> directors{};

        void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept
        {
            os << fill_line_start << "Directors:\n";
            for (const auto& director : directors)
            {
                director.print(os, fill_line_start + 1); os << "\n";
            }
        }
        auto operator<=>(const Directors& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const Directors& directors) { directors.print(os); return os; }


    struct Writer
    {
        std::string name{};

        void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept
        {
            os << fill_line_start << name;
        }
        auto operator<=>(const Writer& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const Writer& writer) { writer.print(os); return os; }

    struct Writers
    {
        std::vector<Writer> writers{};

        void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept
        {
            os << fill_line_start << "Writers:\n";
            for (const auto& writer : writers)
            {
                writer.print(os, fill_line_start + 1); os << "\n";
            }
        }
        auto operator<=>(const Writers& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const Writers& writers) { writers.print(os); return os; }

    struct MediaFile
    {
        size_t id{};
        fs::path file_path{};
        std::optional<std::string> description{};

        void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept
        {
            os << fill_line_start << "Media file:\n";
            os << (fill_line_start + 1) << "id: " << id << "\n";
            os << (fill_line_start + 1) << "path: " << file_path.generic_string() << "\n";
            os << (fill_line_start + 1) << "description: " << description.value_or("") << "\n";
        }
        auto operator<=>(const MediaFile& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const MediaFile& media_file) { media_file.print(os); return os; }

    struct MediaFiles
    {
        std::vector<MediaFile> media_files{};

        void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept
        {
            os << fill_line_start << "Media files:\n";
            for (const auto& media_file : media_files)
            {
                media_file.print(os, fill_line_start + 1);
            }
        }
        auto operator<=>(const MediaFiles& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const MediaFiles& media_files) { media_files.print(os); return os; }

    struct Movie
    {
        size_t id{};
        std::string title{};
        std::chrono::year year{};
        size_t length{};
        Cast cast{};
        Directors directors{};
        Writers writers{};
        MediaFiles media_files{};

        void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept
        {
            os << fill_line_start << "Movie:\n";
            os << (fill_line_start + 1) << "id: " << id << "\n";
            os << (fill_line_start + 1) << "title: " << title << "\n";
            os << (fill_line_start + 1) << "year: " << year << "\n";
            os << (fill_line_start + 1) << "length: " << length << "\n";
            cast.print(os, fill_line_start + 1);
            directors.print(os, fill_line_start + 1);
            writers.print(os, fill_line_start + 1);
            media_files.print(os, fill_line_start + 1);
        }
        auto operator<=>(const Movie& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const Movie& movie) { movie.print(os); return os; }

    struct Catalog
    {
        std::vector<Movie> movies{};

        void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept
        {
            os << fill_line_start << "Catalog:\n";
            for (const auto& movie : movies)
            {
                movie.print(os, fill_line_start + 1);
            }
        }
        auto operator<=>(const Catalog& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const Catalog& catalog) { catalog.print(os); return os; }
}  // namespace rtc::movies


#endif  // MOVIES_H
