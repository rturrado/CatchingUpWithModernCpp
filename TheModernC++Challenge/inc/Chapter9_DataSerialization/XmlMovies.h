#ifndef XML_MOVIES_H
#define XML_MOVIES_H

#include "Chapter9_DataSerialization/pugixml_wrapper.h"

#include "pugixml.hpp"

#include <chrono>
#include <filesystem>
#include <string>
#include <vector>


namespace rtc::xml_movies
{
    struct Role
    {
        std::string star{};
        std::string name{};

        void to_xml(pugi::xml_node& root) const
        {
            rtc::pugixml::append_attribute_or_throw(root, "star") = star.c_str();
            rtc::pugixml::append_attribute_or_throw(root, "name") = name.c_str();
        }

        void from_xml(const pugi::xml_node& root)
        {
            star = rtc::pugixml::attribute_or_throw(root, "star").as_string();
            name = rtc::pugixml::attribute_or_throw(root, "name").as_string();
        }
    };

    inline bool operator==(const Role& lhs, const Role& rhs) { return lhs.star == rhs.star and lhs.name == rhs.name; }


    struct Cast
    {
        std::vector<Role> cast{};

        void to_xml(pugi::xml_node& root) const
        {
            for (auto&& role : cast)
            {
                auto node{ rtc::pugixml::append_child_or_throw(root, "role") }; role.to_xml(node);
            }
        }

        void from_xml(const pugi::xml_node& root)
        {
            for (auto&& node : root.children("role"))
            {
                Role role{};
                role.from_xml(node);
                cast.push_back(role);
            }
        }
    };

    inline bool operator==(const Cast& lhs, const Cast& rhs) { return lhs.cast == rhs.cast; }


    struct Director
    {
        std::string name{};

        void to_xml(pugi::xml_node& root) const { rtc::pugixml::append_attribute_or_throw(root, "name") = name.c_str(); }

        void from_xml(const pugi::xml_node& root) { name = rtc::pugixml::attribute_or_throw(root, "name").as_string(); }
    };

    inline bool operator==(const Director& lhs, const Director& rhs) { return lhs.name == rhs.name; }


    struct Directors
    {
        std::vector<Director> directors{};

        void to_xml(pugi::xml_node& root) const
        {
            for (auto&& director : directors)
            {
                auto node{ rtc::pugixml::append_child_or_throw(root, "director") }; director.to_xml(node);
            }
        }

        void from_xml(const pugi::xml_node& root)
        {
            for (auto&& node : root.children("director"))
            {
                Director director{};
                director.from_xml(node);
                directors.push_back(director);
            }
        }
    };

    inline bool operator==(const Directors& lhs, const Directors& rhs) { return lhs.directors == rhs.directors; }


    struct Writer
    {
        std::string name{};

        void to_xml(pugi::xml_node& root) const { rtc::pugixml::append_attribute_or_throw(root, "name") = name.c_str(); }

        void from_xml(const pugi::xml_node& root) { name = rtc::pugixml::attribute_or_throw(root, "name").as_string(); }
    };

    inline bool operator==(const Writer& lhs, const Writer& rhs) { return lhs.name == rhs.name; }


    struct Writers
    {
        std::vector<Writer> writers{};

        void to_xml(pugi::xml_node& root) const
        {
            for (auto&& writer : writers)
            {
                auto node{ rtc::pugixml::append_child_or_throw(root, "writer") }; writer.to_xml(node);
            }
        }

        void from_xml(const pugi::xml_node& root)
        {
            for (auto&& node : root.children("writer"))
            {
                Writer writer{};
                writer.from_xml(node);
                writers.push_back(writer);
            }
        }
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

        void to_xml(pugi::xml_node& root) const
        {
            using namespace rtc::pugixml;

            append_attribute_or_throw(root, "id") = id;
            append_attribute_or_throw(root, "title") = title.c_str();
            append_attribute_or_throw(root, "year") = static_cast<int>(year);
            append_attribute_or_throw(root, "length") = length;
            { auto node{ append_child_or_throw(root, "cast") }; cast.to_xml(node); }
            { auto node{ append_child_or_throw(root, "directors") }; directors.to_xml(node); }
            { auto node{ append_child_or_throw(root, "writers") }; writers.to_xml(node); }
        }

        void from_xml(const pugi::xml_node& root)
        {
            using namespace rtc::pugixml;

            id = attribute_or_throw(root, "id").as_uint();
            title = attribute_or_throw(root, "title").as_string();
            year = std::chrono::year{ attribute_or_throw(root, "year").as_int() };
            length = attribute_or_throw(root, "length").as_uint();
            cast.from_xml(child_or_throw(root, "cast"));
            directors.from_xml(child_or_throw(root, "directors"));
            writers.from_xml(child_or_throw(root, "writers"));
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


    struct Movies
    {
        std::vector<Movie> movies{};

        void to_xml(pugi::xml_node& root) const
        {
            for (auto&& movie : movies)
            {
                auto node{ rtc::pugixml::append_child_or_throw(root, "movie") }; movie.to_xml(node);
            }
        }

        void from_xml(const pugi::xml_node& root)
        {
            for (auto&& node : root.children("movie"))
            {
                Movie movie{};
                movie.from_xml(node);
                movies.push_back(movie);
            }
        }
    };

    inline bool operator==(const Movies& lhs, const Movies& rhs) { return lhs.movies == rhs.movies; }


    struct Xml
    {
        Movies movies{};

        void to_xml(pugi::xml_document& doc) const
        {
            auto node{ rtc::pugixml::append_child_or_throw(doc, "movies") }; movies.to_xml(node);
        }

        void from_xml(const pugi::xml_document& doc)
        {
            movies.from_xml(rtc::pugixml::child_or_throw(doc, "movies"));
        }

        void save_to(const std::filesystem::path& output_file_path) const
        {
            pugi::xml_document doc{};

            this->to_xml(doc);

            doc.save_file(output_file_path.c_str());
        }

        void load_from(const std::filesystem::path& input_file_path)
        {
            pugi::xml_document doc{};


            rtc::pugixml::load_file_or_throw(doc, input_file_path.string().c_str());

            this->from_xml(doc);
        }
    };

    inline bool operator==(const Xml& lhs, const Xml& rhs) { return lhs.movies == rhs.movies; }
}  // namespace rtc::xml_movies


#endif  // XML_MOVIES_H
