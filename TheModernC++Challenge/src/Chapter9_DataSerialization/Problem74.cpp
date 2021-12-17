#include "Chapter9_DataSerialization.h"
#include "Chapter9_DataSerialization/XmlMovies.h"
#include "Chapter9_DataSerialization/pugixml_wrapper.h"

#include "pugixml.hpp"

#include <cassert>  // assert
#include <chrono>
#include <iostream>  // cout


void print_movies_released_after_year(const rtc::xml_movies::Xml& xml, int year)
{
    std::cout << "Movies released after year: " << year << "\n";

    pugi::xpath_variable_set vars;
    vars.add("year", pugi::xpath_type_number);
    vars.set("year", static_cast<double>(year));
    const pugi::xpath_query query{"/movies/movie[@year > $year]", &vars};
    auto movies{ query.evaluate_node_set(xml.get_root()) };

    for (auto&& movie : movies)
    {
        std::cout << "\t";
        std::cout << rtc::pugixml::attribute_or_throw(movie.node(), "title").as_string() << ", ";
        std::cout << rtc::pugixml::attribute_or_throw(movie.node(), "year").as_int() << "\n";
    }
}


void print_last_actor_in_casting_list_for_every_movie(const rtc::xml_movies::Xml& xml)
{
    std::cout << "Last actor in the casting list for every movie:\n";

    const pugi::xpath_query query{ "/movies/movie" };
    auto movies{ query.evaluate_node_set(xml.get_root()) };

    for (auto&& movie : movies)
    {
        const pugi::xpath_query query{ "cast/role[last()]" };
        auto actor{ query.evaluate_node(movie) };

        std::cout << "\t";
        std::cout << rtc::pugixml::attribute_or_throw(movie.node(), "title").as_string() << ": ";
        std::cout << rtc::pugixml::attribute_or_throw(actor.node(), "star").as_string() << "\n";
    }
}


// Selecting data from XML using XPath
//
// Consider an XML file with a list of movies as described for the previous problem.
// Write a program that can select and print the following:
//
//   - The title of all movies released after a given year.
//   - The name of the last actor in the casting list for each movie in the file.
void problem_74_main()
{
    using namespace rtc::xml_movies;
    using namespace std::chrono_literals;

    const auto temp_file_path{ std::filesystem::temp_directory_path() / "list_of_movies.xml" };

    try
    {
        std::cout << "Writing XML out to: " << temp_file_path << "\n";
        Xml out_xml{
            Movies{{
                {.id = 11001, .title = "The Matrix", .year = 1999y, .length = 196,
                    .cast = Cast{{
                        {.star = "Keanu Reeves", .name = "Neo"},
                        {.star = "Lawrence Fishburne", .name = "Morpheus"},
                        {.star = "Carrie-Anne Moss", .name = "Trinity"},
                        {.star = "Hugo Weaving", .name = "Agent Smith"}
                    }},
                    .directors = Directors{{ {.name = "Lana Wachowski"}, {.name = "Lilly Wachowski"} }},
                    .writers = Writers{{ {.name = "Lana Wachowski"}, {.name = "Lilly Wachowski"} }}
                },
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

        std::cout << "Reading XML in from: " << temp_file_path << "\n\n";
        Xml in_xml{};
        in_xml.load_from(temp_file_path);

        std::cout << "Checking if serializing and deserializing the XML object created the same object... ";
        assert(in_xml == out_xml and "Error: serializing and deserializing the XML object created a different object");
        std::cout << "OK\n\n";

        for (auto year : { 1992, 1996, 2000 })
        {
            print_movies_released_after_year(in_xml, year);
        }
        std::cout << "\n";

        print_last_actor_in_casting_list_for_every_movie(in_xml);
        std::cout << "\n";
    }
    catch (const std::exception& err)
    {
        std::cout << "\"Error: " << err.what() << ".\"\n\n";
    }
}
