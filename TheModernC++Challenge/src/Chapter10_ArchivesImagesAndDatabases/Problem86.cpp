#include "Chapter9_DataSerialization/Movies.h"
#include "Chapter10_ArchivesImagesAndDatabases.h"
#include "Chapter10_ArchivesImagesAndDatabases/ConsoleMovies.h"
#include "Chapter10_ArchivesImagesAndDatabases/FileMovies.h"
#include "Chapter10_ArchivesImagesAndDatabases/SqliteMovies.h"

#include "ConsoleRead.h"

#include <filesystem>
#include <format>
#include <fstream>  // ifstream
#include <iostream>  // cout
#include <sstream>  // ostringstream

namespace fs = std::filesystem;


void add_new_movie(rtc::movies::sqlite_mcpp::database& movies_db, const rtc::movies::Movie& movie)
{
    std::ostringstream oss{};
    oss << movie << "\nAre you sure you want to add this movie to the movies database? [y/n] ";
    auto c{ read_char(oss.str(), { 'n', 'N', 'y', 'Y' }) };
    if (c == 'y' or c == 'Y')
    {
        movies_db.insert_movie(movie);
    }
}

void add_new_movie_from_console(rtc::movies::sqlite_mcpp::database& movies_db)
{
    std::cout << "Please enter the movie data (ID will be later overwritten with DB's Movies.rowid)\n";
    rtc::movies::Movie movie{};
    rtc::movies::console::from_console(movie);
    movie.id = static_cast<int>(movies_db.get_next_movie_id());
    add_new_movie(movies_db, movie);
}

void add_new_movie_from_file(rtc::movies::sqlite_mcpp::database& movies_db)
{
    const fs::path new_movies_file_path{ fs::current_path() / "res" / "db" / "NewMovies.txt" };
    std::cout << "Adding movies from " << new_movies_file_path.generic_string() << "\n";
    std::ifstream ifs{ new_movies_file_path };
    try
    {
        std::string line{};
        std::getline(ifs, line);
        int number_of_movies{ std::stoi(line) };
        while (number_of_movies--)
        {
            rtc::movies::Movie movie{};
            rtc::movies::file::from_file(ifs, movie);
            movie.id = static_cast<int>(movies_db.get_next_movie_id());
            add_new_movie(movies_db, movie);
        }
    }
    catch (const std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << "\n";
    }
}

void add_new_movies(rtc::movies::sqlite_mcpp::database& movies_db)
{
    for (;;)
    {
        auto input_option{ read_char(
            "Choose method for adding a new movie (1 - Console,  2 - File, q - Quit): ",
            { '1', '2', 'q'}
        )};
        switch (input_option)
        {
        case '1': add_new_movie_from_console(movies_db); break;
        case '2': add_new_movie_from_file(movies_db); break;
        case 'q': return;
        default: break;
        }
    }
    std::cout << "\n";
}


// Inserting movies into an SQLite database transactionally
//
// Extend the program written for the previous problem so that it can add new movies to the database.
// The movies could be read from the console, or alternatively from a text file.
// The insertion of movie data into several tables in the database must be performed transactionally.
void problem_86_main()
{
    const auto db_file_path{ fs::current_path() / "res" / "db" / "movies.db" };

    try
    {
        auto sqlite_db{ rtc::movies::sqlite_mcpp::create_movies_database(db_file_path) };
        auto movies_db{ rtc::movies::sqlite_mcpp::database{ sqlite_db } };
        add_new_movies(movies_db);
        std::cout << movies_db;
    }
    catch (const sqlite::sqlite_exception& ex)
    {
        std::cout << std::format("Error: code = {}, message = '{}', operation = '{}'\n",
            ex.get_code(), ex.what(), ex.get_sql());
    }
    catch (const std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << "\n";
    }

    std::cout << "\n";

    rtc::movies::sqlite_mcpp::remove_movies_database_file(db_file_path);

    std::cout << "\n";
}
