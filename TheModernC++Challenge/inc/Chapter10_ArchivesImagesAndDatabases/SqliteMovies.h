#ifndef SQLITE_MOVIES_H
#define SQLITE_MOVIES_H

#include "Chapter9_DataSerialization/Movies.h"

#include "ConsoleRead.h"

#include "sqlite_modern_cpp.h"

#include <algorithm>  // max_element
#include <chrono>
#include <filesystem>
#include <format>
#include <functional>  // less


namespace rtc::movies::sqlite_mcpp
{
    namespace fs = std::filesystem;

    inline auto create_movies_database(const fs::path& db_file_path)
    {
        sqlite::database db{ db_file_path.string() };

        db << "begin;";

        db << "create table if not exists Movies ("
            "title text not null,"
            "year integer not null,"
            "length integer not null"
            ");";
        db << "create table if not exists Persons ("
            "name text not null"
            ");";
        db << "create table if not exists Directors ("
            "movie_id integer not null,"
            "person_id integer not null"
            ");";
        db << "create table if not exists Writers ("
            "movie_id integer not null,"
            "person_id integer not null"
            ");";
        db << "create table if not exists Cast ("
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

        db << "commit;";

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

    inline bool exists_person(sqlite::database& db, const std::string& name)
    {
        bool ret{ false };
        db << "select 1 from Persons where name = (?);" << name
            >> [&ret]() { ret = true; };
        return ret;
    }

    inline int get_person_id(sqlite::database& db, const std::string& name)
    {
        int ret{};
        db << "select rowid from Persons where name = (?);" << name
            >> [&ret](int rowid) { ret = rowid; };
        return ret;
    }

    // Role
    inline void to_db(sqlite::database& db, size_t movie_id, const Role& role)
    {
        size_t person_id{};
        if (exists_person(db, role.star))
        {
            person_id = get_person_id(db, role.star);
        }
        else
        {
            db << "insert into Persons (name) values (?);"
                << role.star;
            person_id = static_cast<int>(db.last_insert_rowid());
        }
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);"
            << movie_id
            << person_id
            << role.name;
    }

    // Cast
    inline void from_db(sqlite::database& db, size_t movie_id, Cast& cast)
    {
        db << "select P.name as name, C.role as role from Persons P join Cast C on P.rowid = C.person_id where C.movie_id = (?);" << movie_id
            >> [&cast](std::string name, std::string role) {
            cast.cast.emplace_back(name, role);
        };
    }
    inline void to_db(sqlite::database& db, size_t movie_id, const Cast& cast)
    {
        for (auto& role : cast.cast)
        {
            to_db(db, movie_id, role);
        }
    }

    // Writer
    inline void to_db(sqlite::database& db, size_t movie_id, const Writer& writer)
    {
        int person_id{};
        if (exists_person(db, writer.name))
        {
            person_id = get_person_id(db, writer.name);
        }
        else
        {
            db << "insert into Persons (name) values (?);"
                << writer.name;
            person_id = static_cast<int>(db.last_insert_rowid());
        }
        db << "insert into Writers (movie_id, person_id) values (?,?);"
            << movie_id
            << person_id;
    }

    // Writers
    inline void from_db(sqlite::database& db, size_t movie_id, Writers& writers)
    {
        db << "select name from Persons P join Writers W on P.rowid = W.person_id where W.movie_id = ?;" << movie_id
            >> [&writers](std::string name) {
            writers.writers.emplace_back(name);
        };
    }
    inline void to_db(sqlite::database& db, size_t movie_id, const Writers& writers)
    {
        for (auto& writer : writers.writers)
        {
            to_db(db, movie_id, writer);
        }
    }

    // Director
    inline void to_db(sqlite::database& db, size_t movie_id, const Director& director)
    {
        int person_id{};
        if (exists_person(db, director.name))
        {
            person_id = get_person_id(db, director.name);
        }
        else
        {
            db << "insert into Persons (name) values (?);"
                << director.name;
            person_id = static_cast<int>(db.last_insert_rowid());
        }
        db << "insert into Directors (movie_id, person_id) values (?,?);"
            << movie_id
            << person_id;
    }

    // Directors
    inline void from_db(sqlite::database& db, size_t movie_id, Directors& directors)
    {
        db << "select name from Persons P join Directors D on P.rowid = D.person_id where D.movie_id = ?;" << movie_id
            >> [&directors](std::string name) {
            directors.directors.emplace_back(name);
        };
    }
    inline void to_db(sqlite::database& db, size_t movie_id, const Directors& directors)
    {
        for (auto& director : directors.directors)
        {
            to_db(db, movie_id, director);
        }
    }

    // Movie
    inline void to_db(sqlite::database& db, const Movie& movie)
    {
        db << "insert into Movies (title,year,length) values (?,?,?);"
            << movie.title
            << static_cast<int>(movie.year)
            << movie.length;
        auto movie_id{ db.last_insert_rowid() };

        to_db(db, static_cast<size_t>(movie_id), movie.cast);
        to_db(db, static_cast<size_t>(movie_id), movie.directors);
        to_db(db, static_cast<size_t>(movie_id), movie.writers);
    }

    // Catalog
    inline void from_db(sqlite::database& db, Catalog& catalog)
    {
        db << "select rowid,title,year,length from Movies;"
            >> [&db, &catalog](int rowid, std::string title, int year, int length) {
            catalog.movies.emplace_back(rowid, title, std::chrono::year{ year }, length);
        };
        for (auto& movie : catalog.movies)
        {
            from_db(db, movie.id, movie.cast);
            from_db(db, movie.id, movie.directors);
            from_db(db, movie.id, movie.writers);
        }
    }

    // database
    struct database
    {
        Catalog catalog{};

        database(sqlite::database& sqlite_db) : sqlite_db_{sqlite_db} { from_db(sqlite_db_, catalog); }

        size_t get_next_movie_id()
        {
            return std::ranges::max_element(catalog.movies, std::less<>{}, &Movie::id)->id + 1;
        }

        void insert_movie(const Movie& m)
        {
            try
            {
                sqlite_db_ << "begin;";
                to_db(sqlite_db_, m);
                sqlite_db_ << "commit;";

                catalog.movies.push_back(m);
            }
            catch (const sqlite::sqlite_exception&)
            {
                sqlite_db_ << "rollback;";
                
                throw;
            }
        }

    private:
        sqlite::database sqlite_db_;
    };
    inline std::ostream& operator<<(std::ostream& os, const database& db) { return os << db.catalog; }

}  // namespace rtc::movies::sqlite_mcpp


#endif  // SQLITE_MOVIES_H
