#include "Chapter9_DataSerialization.h"
#include "Chapter9_DataSerialization/pugixml_wrapper.h"

#include "pugixml.hpp"

#include <cassert>  // assert
#include <chrono>
#include <cstddef>  // ptrdiff_t
#include <filesystem>
#include <iostream>  // cout
#include <string>
#include <vector>


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

bool operator==(const Role& lhs, const Role& rhs) { return lhs.star == rhs.star and lhs.name == rhs.name; }


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

bool operator==(const Cast& lhs, const Cast& rhs) { return lhs.cast == rhs.cast; }


struct Director
{
    std::string name{};

    void to_xml(pugi::xml_node& root) const { rtc::pugixml::append_attribute_or_throw(root, "name") = name.c_str(); }

    void from_xml(const pugi::xml_node& root) { name = rtc::pugixml::attribute_or_throw(root, "name").as_string(); }
};

bool operator==(const Director& lhs, const Director& rhs) { return lhs.name == rhs.name; }


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

bool operator==(const Directors& lhs, const Directors& rhs) { return lhs.directors == rhs.directors; }


struct Writer
{
    std::string name{};

    void to_xml(pugi::xml_node& root) const { rtc::pugixml::append_attribute_or_throw(root, "name") = name.c_str(); }

    void from_xml(const pugi::xml_node& root) { name = rtc::pugixml::attribute_or_throw(root, "name").as_string(); }
};

bool operator==(const Writer& lhs, const Writer& rhs) { return lhs.name == rhs.name; }


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

bool operator==(const Writers& lhs, const Writers& rhs) { return lhs.writers == rhs.writers; }


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

bool operator==(const Movie& lhs, const Movie& rhs)
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

bool operator==(const Movies& lhs, const Movies& rhs) { return lhs.movies == rhs.movies; }


struct XmlFile
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

bool operator==(const XmlFile& lhs, const XmlFile& rhs) { return lhs.movies == rhs.movies; }


// Serializing and deserializing data to/from XML
//
// Write a program that can serialize a list of movies to an XML file, and deserialize an XML file with a list of movies.
// Each movie has a numerical identifier, title, release year, length in minutes, a list of directors, a list of writers,
// and a list of casting roles with actor name and character name.
// Such an XML may look like the following:
//
//   <?xml version="1.0">
//   <movies>
//     <movie id="9871" title="Forrest Gump" year="1994" length="202">
//       <cast>
//         <role star="Tom Hanks" name="Forrest Gump" />
//         <role star="Sally Field" name="Mrs. Gump" />
//         <role star="Robin Wright" name="Jenny Curran" />
//         <role star="Mykelti Williamson" name="Bubba Blue" />
//       </cast>
//       <directors>
//         <director name="Robert Zemeckis" />
//       </directors>
//       <writers>
//         <writer name="Winston Groom" />
//         <writer name="Eric Roth" />
//       </writers>
//     </movie>
//     <!-- more movie elements -->
//   </movies>
void problem_73_main()
{
    using namespace std::chrono_literals;

    const auto temp_file_path{ std::filesystem::temp_directory_path() / "list_of_movies.xml" };

    try
    {
        std::cout << "Writing XML out to: " << temp_file_path << "\n";
        const XmlFile out_xml{
            .movies = Movies{{
                {.id = 9871, .title = "Forrest Gump", .year = 1994y, .length = 202,
                    .cast = Cast{{
                        {.star = "Tom Hanks", .name = "Forrest Gump"},
                        {.star = "Sally Field", .name = "Mrs. Gump"},
                        {.star = "Robin Wright", .name = "Jenny Curran"},
                        {.star = "Mykelti Williamson", .name = "Bubba Blue"}
                    }},
                    .directors = Directors{{ {.name = "Robert Zemeckis"} }},
                    .writers = Writers{{ {.name = "Winston Groom"}, {.name = "Eric Roth"} }}
                }
            }}
        };
        out_xml.save_to(temp_file_path);

        std::cout << "Reading XML in from: " << temp_file_path << "\n";
        XmlFile in_xml{};
        in_xml.load_from(temp_file_path);

        std::cout << "Checking if serializing and deserializing the XML object created the same object... ";
        assert(in_xml == out_xml and "Error: serializing and deserializing the XML object created a different object");
        std::cout << "OK\n";
    }
    catch (const std::exception& err)
    {
        std::cout << "Error: " << err.what() << ".\n";
    }

    std::cout << "\n";
}
