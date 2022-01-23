#include "Chapter10_ArchivesImagesAndDatabases.h"
#include "Chapter10_ArchivesImagesAndDatabases/zip_lib_wrapper.h"

// Compressing and decompressing files to/from a ZIP archive
//
// Write a program that can do the following:
//   - Compress either a file or the contents of a user-specified directory, recursively, to a ZIP archive.
//   - Decompress the contents of a ZIP archive to a user-specified destination directory.
void problem_80_main()
{
    rtc::zip_lib_wrapper::test();
}
