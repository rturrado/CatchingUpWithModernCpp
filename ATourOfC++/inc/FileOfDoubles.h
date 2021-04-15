#ifndef __FILE_OF_DOUBLES_H__
#define __FILE_OF_DOUBLES_H__

#include <string>
#include <vector>

class File_of_doubles
{
public:
    void add_line(std::string line);
    void print_data();
private:
    typedef std::vector<double> row;
    std::vector<row> data;
};

void file_of_doubles_main();

#endif
