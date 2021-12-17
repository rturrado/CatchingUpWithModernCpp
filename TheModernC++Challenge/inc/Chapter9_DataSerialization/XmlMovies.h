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

        void save_to_xml_node(pugi::xml_node& root) const
        {
            rtc::pugixml::append_attribute_or_throw(root, "star") = star.c_str();
            rtc::pugixml::append_attribute_or_throw(root, "name") = name.c_str();
        }

        void load_from_xml_node(const pugi::xml_node& root)
        {
            star = rtc::pugixml::attribute_or_throw(root, "star").as_string();
            name = rtc::pugixml::attribute_or_throw(root, "name").as_string();
        }
    };

    inline bool operator==(const Role& lhs, const Role& rhs) { return lhs.star == rhs.star and lhs.name == rhs.name; }


    struct Cast
    {
        std::vector<Role> cast{};

        void save_to_xml_node(pugi::xml_node& root) const
        {
            for (auto&& role : cast)
            {
                auto node{ rtc::pugixml::append_child_or_throw(root, "role") }; role.save_to_xml_node(node);
            }
        }

        void load_from_xml_node(const pugi::xml_node& root)
        {
            for (auto&& node : root.children("role"))
            {
                Role role{};
                role.load_from_xml_node(node);
                cast.push_back(role);
            }
        }
    };

    inline bool operator==(const Cast& lhs, const Cast& rhs) { return lhs.cast == rhs.cast; }


    struct Director
    {
        std::string name{};

        void save_to_xml_node(pugi::xml_node& root) const { rtc::pugixml::append_attribute_or_throw(root, "name") = name.c_str(); }

        void load_from_xml_node(const pugi::xml_node& root) { name = rtc::pugixml::attribute_or_throw(root, "name").as_string(); }
    };

    inline bool operator==(const Director& lhs, const Director& rhs) { return lhs.name == rhs.name; }


    struct Directors
    {
        std::vector<Director> directors{};

        void save_to_xml_node(pugi::xml_node& root) const
        {
            for (auto&& director : directors)
            {
                auto node{ rtc::pugixml::append_child_or_throw(root, "director") }; director.save_to_xml_node(node);
            }
        }

        void load_from_xml_node(const pugi::xml_node& root)
        {
            for (auto&& node : root.children("director"))
            {
                Director director{};
                director.load_from_xml_node(node);
                directors.push_back(director);
            }
        }
    };

    inline bool operator==(const Directors& lhs, const Directors& rhs) { return lhs.directors == rhs.directors; }


    struct Writer
    {
        std::string name{};

        void save_to_xml_node(pugi::xml_node& root) const { rtc::pugixml::append_attribute_or_throw(root, "name") = name.c_str(); }

        void load_from_xml_node(const pugi::xml_node& root) { name = rtc::pugixml::attribute_or_throw(root, "name").as_string(); }
    };

    inline bool operator==(const Writer& lhs, const Writer& rhs) { return lhs.name == rhs.name; }


    struct Writers
    {
        std::vector<Writer> writers{};

        void save_to_xml_node(pugi::xml_node& root) const
        {
            for (auto&& writer : writers)
            {
                auto node{ rtc::pugixml::append_child_or_throw(root, "writer") }; writer.save_to_xml_node(node);
            }
        }

        void load_from_xml_node(const pugi::xml_node& root)
        {
            for (auto&& node : root.children("writer"))
            {
                Writer writer{};
                writer.load_from_xml_node(node);
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

        void save_to_xml_node(pugi::xml_node& root) const
        {
            using namespace rtc::pugixml;

            append_attribute_or_throw(root, "id") = id;
            append_attribute_or_throw(root, "title") = title.c_str();
            append_attribute_or_throw(root, "year") = static_cast<int>(year);
            append_attribute_or_throw(root, "length") = length;
            { auto node{ append_child_or_throw(root, "cast") }; cast.save_to_xml_node(node); }
            { auto node{ append_child_or_throw(root, "directors") }; directors.save_to_xml_node(node); }
            { auto node{ append_child_or_throw(root, "writers") }; writers.save_to_xml_node(node); }
        }

        void load_from_xml_node(const pugi::xml_node& root)
        {
            using namespace rtc::pugixml;

            id = attribute_or_throw(root, "id").as_uint();
            title = attribute_or_throw(root, "title").as_string();
            year = std::chrono::year{ attribute_or_throw(root, "year").as_int() };
            length = attribute_or_throw(root, "length").as_uint();
            cast.load_from_xml_node(child_or_throw(root, "cast"));
            directors.load_from_xml_node(child_or_throw(root, "directors"));
            writers.load_from_xml_node(child_or_throw(root, "writers"));
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
    
        void save_to_xml_node(pugi::xml_node& root) const
        {
            for (auto&& movie : movies)
            {
                auto node{ rtc::pugixml::append_child_or_throw(root, "movie") }; movie.save_to_xml_node(node);
            }
        }

        void load_from_xml_node(const pugi::xml_node& root)
        {
            for (auto&& node : root.children("movie"))
            {
                Movie movie{};
                movie.load_from_xml_node(node);
                movies.push_back(movie);
            }
        }

    };

    inline bool operator==(const Movies& lhs, const Movies& rhs) { return lhs.movies == rhs.movies; }


    struct Xml
    {
        Movies movies{};

        Xml() = default;
        Xml(const Movies& mvs) : movies{ mvs } {}

        void save_to(const std::filesystem::path& output_file_path)
        {
            save_to_xml_document();

            rtc::pugixml::save_xml_document_to_file_or_throw(doc_, output_file_path.string().c_str());
        }

        void load_from(const std::filesystem::path& input_file_path)
        {
            rtc::pugixml::load_xml_document_from_file_or_throw(doc_, input_file_path.string().c_str());

            load_from_xml_document();
        }

        [[nodiscard]] const pugi::xml_node& get_root() const { return doc_.root(); }

    private:
        // doc_ should be used as a cache, but it isn't at the moment
        // We load from file to doc_, and then from doc_ to the different structs
        // We save from the different structs to doc_, and then to file
        // We never check if the structs contents have changed, so we could avoid writing to doc_ and even to file
        // That same check would be mandatory before querying doc_ directly, once loaded (e.g. problem 74)
        pugi::xml_document doc_{};

        void save_to_xml_document()
        {
            auto node{ rtc::pugixml::append_child_or_throw(doc_, "movies") }; movies.save_to_xml_node(node);
        }

        void load_from_xml_document()
        {
            movies.load_from_xml_node(rtc::pugixml::child_or_throw(doc_, "movies"));
        }
    };

    inline bool operator==(const Xml& lhs, const Xml& rhs) { return lhs.movies == rhs.movies; }
}  // namespace rtc::xml_movies


#endif  // XML_MOVIES_H
