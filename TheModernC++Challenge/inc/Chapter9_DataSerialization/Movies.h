#ifndef MOVIES_H
#define MOVIES_H

#include <chrono>
#include <string>
#include <vector>


namespace rtc::movies
{
    struct Role
    {
        std::string star{};
        std::string name{};
    };
    inline bool operator==(const Role& lhs, const Role& rhs) { return lhs.star == rhs.star and lhs.name == rhs.name; }


    struct Cast
    {
        std::vector<Role> cast{};
    };
    inline bool operator==(const Cast& lhs, const Cast& rhs) { return lhs.cast == rhs.cast; }


    struct Director
    {
        std::string name{};
    };
    inline bool operator==(const Director& lhs, const Director& rhs) { return lhs.name == rhs.name; }


    struct Directors
    {
        std::vector<Director> directors{};
    };
    inline bool operator==(const Directors& lhs, const Directors& rhs) { return lhs.directors == rhs.directors; }


    struct Writer
    {
        std::string name{};
    };
    inline bool operator==(const Writer& lhs, const Writer& rhs) { return lhs.name == rhs.name; }


    struct Writers
    {
        std::vector<Writer> writers{};
    };
    inline bool operator==(const Writers& lhs, const Writers& rhs) { return lhs.writers == rhs.writers; }


    struct Movie
    {
        size_t id{};
        std::string title{};
        std::chrono::year year{};
        size_t length{};
        Cast cast{};
        Directors directors{};
        Writers writers{};
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

    struct Catalog
    {
        std::vector<Movie> movies{};
    };
    inline bool operator==(const Catalog& lhs, const Catalog& rhs) { return lhs.movies == rhs.movies; }
}  // namespace rtc::movies


#endif  // MOVIES_H
