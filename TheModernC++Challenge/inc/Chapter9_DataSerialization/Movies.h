#ifndef MOVIES_H
#define MOVIES_H

#include "PrettyPrint.h"

#include <chrono>
#include <ostream>
#include <string>
#include <vector>


namespace rtc::movies
{
    struct Role
    {
        std::string star{};
        std::string name{};

        void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept
        {
            os << fill_line_start << star << " (" << name << ")";
        }
    };
    inline bool operator==(const Role& lhs, const Role& rhs) { return lhs.star == rhs.star and lhs.name == rhs.name; }
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
    };
    inline bool operator==(const Cast& lhs, const Cast& rhs) { return lhs.cast == rhs.cast; }
    inline std::ostream& operator<<(std::ostream& os, const Cast& cast) { cast.print(os); return os; }

    struct Director
    {
        std::string name{};

        void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept
        {
            os << fill_line_start << name;
        }
    };
    inline bool operator==(const Director& lhs, const Director& rhs) { return lhs.name == rhs.name; }
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
    };
    inline bool operator==(const Directors& lhs, const Directors& rhs) { return lhs.directors == rhs.directors; }
    inline std::ostream& operator<<(std::ostream& os, const Directors& directors) { directors.print(os); return os; }


    struct Writer
    {
        std::string name{};

        void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept
        {
            os << fill_line_start << name;
        }
    };
    inline bool operator==(const Writer& lhs, const Writer& rhs) { return lhs.name == rhs.name; }
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
    };
    inline bool operator==(const Writers& lhs, const Writers& rhs) { return lhs.writers == rhs.writers; }
    inline std::ostream& operator<<(std::ostream& os, const Writers& writers) { writers.print(os); return os; }

    struct Movie
    {
        size_t id{};
        std::string title{};
        std::chrono::year year{};
        size_t length{};
        Cast cast{};
        Directors directors{};
        Writers writers{};

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
        }
    };
    inline bool operator==(const Movie& lhs, const Movie& rhs)
    {
        return lhs.id == rhs.id
            and lhs.title == rhs.title
            and lhs.year == rhs.year
            and lhs.length == rhs.length
            and lhs.cast == rhs.cast
            and lhs.directors == rhs.directors
            and lhs.writers == rhs.writers;
    }
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
    };
    inline bool operator==(const Catalog& lhs, const Catalog& rhs) { return lhs.movies == rhs.movies; }
    inline std::ostream& operator<<(std::ostream& os, const Catalog& catalog) { catalog.print(os); return os; }
}  // namespace rtc::movies


#endif  // MOVIES_H
