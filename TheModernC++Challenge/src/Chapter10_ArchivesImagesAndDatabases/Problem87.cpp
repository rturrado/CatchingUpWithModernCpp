#include "Chapter10_ArchivesImagesAndDatabases.h"

#include <iostream>  // cout

// Handling movie images in an SQLite database
//
// Modify the program written for the previous problem to support adding media files (such as images, but also videos) to a movie.
// These files must be stored in a separate table in the database and have a unique numerical identifier, the movie identifier,
// a name (typically the filename), an optional description, and the actual media content, stored as a blob.
// The following is a diagram with the structure of the table that must be added to the existing database:
//
//   media
//   --------------------------
//   (key) rowid        integer
//         movieid      integer
//         name         text
//         description  text
//         content      blob
//
// The program written for this problem must support several commands:
//   - Listing all movies that match a search criterion (notably the title).
//   - Listing information about all existing media files for a movie.
//   - Adding a new media file for a movie.
//   - Deleting an existing media file.
void problem_87_main()
{
    std::cout << "\n";
}
