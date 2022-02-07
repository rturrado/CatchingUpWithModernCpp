#ifndef JSON_MOVIES_H
#define JSON_MOVIES_H

#include "Movies.h"

#include "nlohmann/json.hpp"

#include <filesystem>
#include <fstream>  // ifstream, ofstream
#include <vector>


// nlohmann json requires to_json and from_json functions
// to be in the same namespace as the types it works on
namespace rtc::movies
{
    // Role
    inline void to_json(nlohmann::json& j, const Role& role)
    {
        j = nlohmann::json{ {"star", role.star}, {"name", role.name} };
    }
    inline void from_json(const nlohmann::json& j, Role& role)
    {
        j.at("star").get_to(role.star);
        j.at("name").get_to(role.name);
    }

    // Cast
    inline void to_json(nlohmann::json& j, const Cast& cast)
    {
        j = cast.cast;
    }
    inline void from_json(const nlohmann::json& j, Cast& cast)
    {
        cast.cast = j.get<std::vector<Role>>();
    }

    // Director
    inline void to_json(nlohmann::json& j, const Director& director)
    {
        j = director.name;
    }
    inline void from_json(const nlohmann::json& j, Director& director)
    {
        j.get_to(director.name);
    }

    // Directors
    inline void to_json(nlohmann::json& j, const Directors& directors)
    {
        j = directors.directors;
    }
    inline void from_json(const nlohmann::json& j, Directors& directors)
    {
        directors.directors = j.get<std::vector<Director>>();
    }

    // Writer
    inline void to_json(nlohmann::json& j, const Writer& writer)
    {
        j = writer.name;
    }
    inline void from_json(const nlohmann::json& j, Writer& writer)
    {
        j.get_to(writer.name);
    }

    // Writers
    inline void to_json(nlohmann::json& j, const Writers& writers)
    {
        j = writers.writers;
    }
    inline void from_json(const nlohmann::json& j, Writers& writers)
    {
        writers.writers = j.get<std::vector<Writer>>();
    }

    // Movie
    inline void to_json(nlohmann::json& j, const Movie& movie)
    {
        j = nlohmann::json{
            { "id", movie.id },
            { "title", movie.title },
            { "year", static_cast<int>(movie.year) },
            { "length", movie.length },
            { "cast", movie.cast },
            { "directors", movie.directors },
            { "writers", movie.writers }
        };
    }
    inline void from_json(const nlohmann::json& j, Movie& movie)
    {
        j.at("id").get_to(movie.id);
        j.at("title").get_to(movie.title);
        movie.year = std::chrono::year{ j.at("year").get<int>() };
        j.at("length").get_to(movie.length);
        j.at("cast").get_to(movie.cast);
        j.at("directors").get_to(movie.directors);
        j.at("writers").get_to(movie.writers);
    }

    // Catalog
    inline void to_json(nlohmann::json& j, const Catalog& catalog)
    {
        j = { "movies", catalog.movies };
    }
    inline void from_json(const nlohmann::json& j, Catalog& catalog)
    {
        catalog.movies = j.get<std::vector<Movie>>();
    }

    // doc
    struct doc
    {
        Catalog catalog{};

        doc() = default;
        doc(const Catalog& c) : catalog{ c } {}

        void save_to(const std::filesystem::path& output_file_path)
        {
            std::ofstream ofs{ output_file_path };
            ofs << std::setw(4) << nlohmann::json{ catalog } << "\n";
        }
        void load_from(const std::filesystem::path& input_file_path)
        {
            std::ifstream ifs{ input_file_path };
            nlohmann::json j{};
            ifs >> j;
            j.at("movies").get_to(catalog);
        }
    };
    inline bool operator==(const doc& lhs, const doc& rhs) { return lhs.catalog == rhs.catalog; }

}  // namespace rtc::movies


#endif  // JSON_MOVIES_H
