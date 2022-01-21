#include "Chapter9_DataSerialization.h"
#include "Chapter9_DataSerialization/Movies.h"
#include "Chapter9_DataSerialization/JsonMovies.h"

#include <iostream>  // cout


// Serializing data to JSON
//
// Write a program that can serialize a list of movies, as defined for the previous problems, to a JSON file.
// Each movie has a numerical identifier, title, release year, length in minutes, a list of directors, a list of writers,
// and a list of casting roles with actor name and character name.
// The following is an example of the expected JSON format:
//
//    {
//        "movies" : [{
//            "id": 9871,
//            "title": "Forrest Gump",
//            "year": 1994,
//            "length": 202,
//            "cast": [{
//                "star": "Tom Hanks",
//                "name": "Forrest Gump",
//            },
//            {
//                "star": "Sally Field",
//                "name": "Mrs. Gump",
//            },
//            {
//                "star": "Robin Wright",
//                "name": "Jenny Curran",
//            },
//            {
//                "star": "Mykelti Williamson",
//                "name": "Bubba Blue",
//            }
//            }],
//            "directors": ["Robert Zemeckis"],
//            "writers": ["Winston Groom", "Eric Roth"],
//        }]
//    }
void problem_75_main()
{
    using namespace std::chrono_literals;

    const auto temp_file_path{ std::filesystem::temp_directory_path() / "list_of_movies.json" };

    try
    {
        std::cout << "Writing JSON out to: " << temp_file_path << "\n";
        rtc::movies::doc out_doc{
            rtc::movies::Catalog{{
                {.id = 9871, .title = "Forrest Gump", .year = 1994y, .length = 202,
                    .cast = rtc::movies::Cast{{
                        {.star = "Tom Hanks", .name = "Forrest Gump"},
                        {.star = "Sally Field", .name = "Mrs. Gump"},
                        {.star = "Robin Wright", .name = "Jenny Curran"},
                        {.star = "Mykelti Williamson", .name = "Bubba Blue"}
                    }},
                    .directors = rtc::movies::Directors{{ {.name = "Robert Zemeckis"} }},
                    .writers = rtc::movies::Writers{{ {.name = "Winston Groom"}, {.name = "Eric Roth"} }}
                }
            }}
        };
        out_doc.save_to(temp_file_path);

        std::cout << "Reading JSON in from: " << temp_file_path << "\n\n";
        rtc::movies::doc in_doc{};
        in_doc.load_from(temp_file_path);

        std::cout << "Checking if serializing and deserializing the JSON object created the same object... ";
        assert(in_doc == out_doc and "Error: serializing and deserializing the JSON object created a different object");
        std::cout << "OK\n\n";
    }
    catch (const std::exception& err)
    {
        std::cout << "\"Error: " << err.what() << "\"\n\n";
    }
}
