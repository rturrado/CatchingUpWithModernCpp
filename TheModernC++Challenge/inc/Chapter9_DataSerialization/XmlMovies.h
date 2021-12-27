#ifndef XML_MOVIES_H
#define XML_MOVIES_H

#include "Movies.h"
#include "pugixml_wrapper.h"

#include "pugixml.hpp"

#include <filesystem>


namespace rtc::movies::xml
{
    // Role
    inline void to_xml(pugi::xml_node& root, const Role& role)
    {
        rtc::pugixml::append_attribute_or_throw(root, "star") = role.star.c_str();
        rtc::pugixml::append_attribute_or_throw(root, "name") = role.name.c_str();
    }
    inline void from_xml(const pugi::xml_node& root, Role& role)
    {
        role.star = rtc::pugixml::attribute_or_throw(root, "star").as_string();
        role.name = rtc::pugixml::attribute_or_throw(root, "name").as_string();
    }

    // Cast
    inline void to_xml(pugi::xml_node& root, const Cast& cast)
    {
        for (auto&& role : cast.cast)
        {
            auto node{ rtc::pugixml::append_child_or_throw(root, "role") }; to_xml(node, role);
        }
    }
    inline void from_xml(const pugi::xml_node& root, Cast& cast)
    {
        for (auto&& node : root.children("role"))
        {
            Role role{};
            from_xml(node, role);
            cast.cast.push_back(role);
        }
    }

    // Director
    inline void to_xml(pugi::xml_node& root, const Director& director)
    {
        rtc::pugixml::append_attribute_or_throw(root, "name") = director.name.c_str();
    }
    inline void from_xml(const pugi::xml_node& root, Director& director)
    {
        director.name = rtc::pugixml::attribute_or_throw(root, "name").as_string();
    }

    // Directors
    inline void to_xml(pugi::xml_node& root, const Directors& directors)
    {
        for (auto&& director : directors.directors)
        {
            auto node{ rtc::pugixml::append_child_or_throw(root, "director") }; to_xml(node, director);
        }
    }
    inline void from_xml(const pugi::xml_node& root, Directors& directors)
    {
        for (auto&& node : root.children("director"))
        {
            Director director{};
            from_xml(node, director);
            directors.directors.push_back(director);
        }
    }

    // Writer
    inline void to_xml(pugi::xml_node& root, const Writer& writer)
    {
        rtc::pugixml::append_attribute_or_throw(root, "name") = writer.name.c_str();
    }
    inline void from_xml(const pugi::xml_node& root, Writer& writer)
    {
        writer.name = rtc::pugixml::attribute_or_throw(root, "name").as_string();
    }

    // Writers
    inline void to_xml(pugi::xml_node& root, const Writers& writers)
    {
        for (auto&& writer : writers.writers)
        {
            auto node{ rtc::pugixml::append_child_or_throw(root, "writer") }; to_xml(node, writer);
        }
    }
    inline void from_xml(const pugi::xml_node& root, Writers& writers)
    {
        for (auto&& node : root.children("writer"))
        {
            Writer writer{};
            from_xml(node, writer);
            writers.writers.push_back(writer);
        }
    }

    // Movie
    inline void to_xml(pugi::xml_node& root, const Movie& movie)
    {
        using namespace rtc::pugixml;

        append_attribute_or_throw(root, "id") = movie.id;
        append_attribute_or_throw(root, "title") = movie.title.c_str();
        append_attribute_or_throw(root, "year") = static_cast<int>(movie.year);
        append_attribute_or_throw(root, "length") = movie.length;
        { auto node{ append_child_or_throw(root, "cast") }; to_xml(node, movie.cast); }
        { auto node{ append_child_or_throw(root, "directors") }; to_xml(node, movie.directors); }
        { auto node{ append_child_or_throw(root, "writers") }; to_xml(node, movie.writers); }
    }
    inline void from_xml(const pugi::xml_node& root, Movie& movie)
    {
        using namespace rtc::pugixml;

        movie.id = attribute_or_throw(root, "id").as_uint();
        movie.title = attribute_or_throw(root, "title").as_string();
        movie.year = std::chrono::year{ attribute_or_throw(root, "year").as_int() };
        movie.length = attribute_or_throw(root, "length").as_uint();
        from_xml(child_or_throw(root, "cast"), movie.cast);
        from_xml(child_or_throw(root, "directors"), movie.directors);
        from_xml(child_or_throw(root, "writers"), movie.writers);
    }

    // Catalog
    inline void to_xml(pugi::xml_node& root, const Catalog& catalog)
    {
        for (auto&& movie : catalog.movies)
        {
            auto node{ rtc::pugixml::append_child_or_throw(root, "movie") }; to_xml(node, movie);
        }
    }
    inline void from_xml(const pugi::xml_node& root, Catalog& catalog)
    {
        for (auto&& node : root.children("movie"))
        {
            Movie movie{};
            from_xml(node, movie);
            catalog.movies.push_back(movie);
        }
    }

    // doc
    struct doc
    {
        Catalog catalog{};

        doc() = default;
        doc(const Catalog& c) : catalog{ c } {}

        [[nodiscard]] const pugi::xml_node& get_pugi_xml_root() const { return pugi_xml_doc_.root(); }

        void save_to(const std::filesystem::path& output_file_path)
        {
            auto node{ rtc::pugixml::append_child_or_throw(pugi_xml_doc_, "movies") }; to_xml(node, catalog);

            rtc::pugixml::save_xml_document_to_file_or_throw(pugi_xml_doc_, output_file_path.string().c_str());
        }
        void load_from(const std::filesystem::path& input_file_path)
        {
            rtc::pugixml::load_xml_document_from_file_or_throw(pugi_xml_doc_, input_file_path.string().c_str());

            from_xml(rtc::pugixml::child_or_throw(pugi_xml_doc_, "movies"), catalog);
        }

    private:
        // doc_ should be used as a cache, but it isn't at the moment
        // We load from file to doc_, and then from doc_ to the different structs
        // We save from the different structs to doc_, and then to file
        // We never check if the structs contents have changed, so we could avoid writing to doc_ and even to file
        // That same check would be mandatory before querying doc_ directly, once loaded (e.g. problem 74)
        pugi::xml_document pugi_xml_doc_{};
    };
    inline bool operator==(const doc& lhs, const doc& rhs) { return lhs.catalog == rhs.catalog; }


}  // namespace rtc::movies::xml


#endif  // XML_MOVIES_H
