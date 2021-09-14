export module FileOfDoubles;

import <exception>;
import <fstream>;
import <iostream>;
import <sstream>;
import <string>;
import <vector>;

class File_of_doubles
{
public:
    void add_line(std::string line);
    void print_data();
private:
    typedef std::vector<double> row;
    std::vector<row> data;
};

void File_of_doubles::add_line(std::string line)
{
    std::stringstream ss{ line };
    std::string number;
    std::vector<double> row;
    while (ss >> number)
    {
        try
        {
            row.push_back(std::stod(number));
        }
        catch (const std::invalid_argument& err)
        {
            std::cout << "Error: " << err.what() << "\n";
            throw;
        }
        catch (const std::out_of_range& err)
        {
            std::cout << "Error: " << err.what() << "\n";
            throw;
        }
    }
    data.push_back(row);
}

void File_of_doubles::print_data()
{
    for (const auto& row : data)
    {
        bool first = true;
        for (const auto& number : row)
        {
            std::cout << (first ? "" : " ") << number;
            first = false;
        }
        std::cout << "\n";
    }
}

export void file_of_doubles_main()
{
    std::ifstream file("file_of_doubles.txt");
    File_of_doubles file_of_doubles;

    std::cout << "Reading from file:\n";
    for (std::string line; getline(file, line); )
    {
        std::cout << line << "\n";
        file_of_doubles.add_line(line);
    }
    std::cout << "\n";

    std::cout << "Printing data:\n";
    file_of_doubles.print_data();

    file.close();
}
