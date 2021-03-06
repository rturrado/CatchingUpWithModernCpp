#include "Chapter9_DataSerialization.h"
#include "Chapter9_DataSerialization/Movies.h"
#include "Chapter9_DataSerialization/XmlMovies.h"

#include <cassert>  // assert
#include <chrono>
#include <filesystem>
#include <iostream>  // cout


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
        rtc::movies::xml::doc out_doc{
            rtc::movies::Catalog{{
                {   .id = 9871, .title = "Forrest Gump", .year = 1994y, .length = 202,
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

        std::cout << "Reading XML in from: " << temp_file_path << "\n\n";
        rtc::movies::xml::doc in_doc{};
        in_doc.load_from(temp_file_path);

        std::cout << "Checking if serializing and deserializing the XML object created the same object... ";
        assert(in_doc == out_doc and "Error: serializing and deserializing the XML object created a different object");
        std::cout << "OK\n\n";
    }
    catch (const std::exception& err)
    {
        std::cout << "\"Error: " << err.what() << "\"\n\n";
    }
}
