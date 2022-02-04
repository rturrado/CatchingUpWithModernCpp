#ifndef SQLITE_MOVIES_H
#define SQLITE_MOVIES_H

#include "ConsoleRead.h"

#include "Chapter9_DataSerialization/Movies.h"

#include <sqlite_modern_cpp.h>

#include <chrono>
#include <filesystem>
#include <format>


namespace rtc::movies::sqlite_mcpp
{
    namespace fs = std::filesystem;

    inline auto create_movies_database(const fs::path& db_file_path)
    {
        sqlite::database db{ db_file_path.string() };

        db << "create table if not exists Movies ("
            "_id integer primary key autoincrement not null,"
            "title text not null,"
            "year integer not null,"
            "length integer not null"
            ");";
        db << "create table if not exists Persons ("
            "_id integer primary key autoincrement not null,"
            "name text not null"
            ");";
        db << "create table if not exists Directors ("
            "_id integer primary key autoincrement not null,"
            "movie_id integer not null,"
            "person_id integer not null"
            ");";
        db << "create table if not exists Writers ("
            "_id integer primary key autoincrement not null,"
            "movie_id integer not null,"
            "person_id integer not null"
            ");";
        db << "create table if not exists Cast ("
            "_id integer primary key autoincrement not null,"
            "movie_id integer not null,"
            "person_id integer not null,"
            "role text not null"
            ");";

        db << "insert into Movies (title, year, length) values (?,?,?);" << "The Matrix" << 1999 << 196;
        db << "insert into Movies (title, year, length) values (?,?,?);" << "Forrest Gump" << 1994 << 202;

        db << "insert into Persons (name) values (?);" << "Keanu Reeves";
        db << "insert into Persons (name) values (?);" << "Laurence Fishburne";
        db << "insert into Persons (name) values (?);" << "Carrie - Anne Moss";
        db << "insert into Persons (name) values (?);" << "Hugo Weaving";
        db << "insert into Persons (name) values (?);" << "Lana Wachowski";
        db << "insert into Persons (name) values (?);" << "Lilly Wachowski";
        db << "insert into Persons (name) values (?);" << "Tom Hanks";
        db << "insert into Persons (name) values (?);" << "Sally Field";
        db << "insert into Persons (name) values (?);" << "Robin Wright";
        db << "insert into Persons (name) values (?);" << "Mykelti Williamson";
        db << "insert into Persons (name) values (?);" << "Robert Zemeckis";
        db << "insert into Persons (name) values (?);" << "Winston Groom";
        db << "insert into Persons (name) values (?);" << "Eric Roth";

        db << "insert into directors (movie_id, person_id) values (?,?);" << 1 << 5;
        db << "insert into directors (movie_id, person_id) values (?,?);" << 1 << 6;
        db << "insert into directors (movie_id, person_id) values (?,?);" << 2 << 11;

        db << "insert into Writers (movie_id, person_id) values (?,?);" << 1 << 5;
        db << "insert into Writers (movie_id, person_id) values (?,?);" << 1 << 6;
        db << "insert into Writers (movie_id, person_id) values (?,?);" << 2 << 12;
        db << "insert into Writers (movie_id, person_id) values (?,?);" << 2 << 13;

        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 1 << 1 << "Neo";
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 1 << 2 << "Morpheus";
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 1 << 3 << "Trinity";
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 1 << 4 << "Agent Smith";
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 2 << 7 << "Forrest Gump";
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 2 << 8 << "Mrs.Gump";
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 2 << 9 << "Jenny Curran";
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 2 << 10 << "Bubba Blue";

        return db;
    }

    inline auto remove_movies_database_file(const fs::path& db_file_path)
    {
        auto c{
            read_char(
                std::format("Are you sure you want to remove '{}'? [y/n] ", db_file_path.string()),
                std::vector<char>{'n', 'N', 'y', 'Y'})
        };
        if (c == 'y' or c == 'Y')
        {
            fs::remove(db_file_path);
        }
    }

    // Cast
    inline void from_db(sqlite::database& db, int movie_id, Cast& cast)
    {
        db << "select P.name as name, C.role as role from Persons P join Cast C where C.movie_id = ? and P._id = C.person_id;" << movie_id
            >> [&cast](std::string name, std::string role) {
            cast.cast.emplace_back(name, role);
        };
    }

    // Writers
    inline void from_db(sqlite::database& db, int movie_id, Writers& writers)
    {
        db << "select name from Persons P join Writers W where P._id = W.person_id and W.movie_id = ?;" << movie_id
            >> [&writers](std::string name) {
            writers.writers.emplace_back(name);
        };
    }

    // Directors
    inline void from_db(sqlite::database& db, int movie_id, Directors& directors)
    {
        db << "select name from Persons P join Directors D where P._id = D.person_id and D.movie_id = ?;" << movie_id
            >> [&directors](std::string name) {
            directors.directors.emplace_back(name);
        };
    }

    // Catalog
    inline void from_db(sqlite::database& db, Catalog& catalog)
    {
        db << "select _id,title,year,length from Movies;"
            >> [&db, &catalog](int _id, std::string title, int year, int length) {
            catalog.movies.emplace_back(_id, title, std::chrono::year{ year }, length);
        };
        for (auto& movie : catalog.movies)
        {
            from_db(db, movie.id, movie.cast);
            from_db(db, movie.id, movie.writers);
            from_db(db, movie.id, movie.directors);
        }
    }

    // database
    struct database
    {
        Catalog catalog{};

        database() = default;
        database(const Catalog& c) : catalog{ c } {}

        void load_from(sqlite::database& sqlite_db)
        {
            from_db(sqlite_db, catalog);
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const database& db) { return os << db.catalog; }
}  // namespace rtc::movies::sqlite_mcpp


#endif  // SQLITE_MOVIES_H
