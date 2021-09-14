export module Istreams;

import <algorithm>;
import <ios>;
import <iostream>;
import <regex>;
import <string>;
import <vector>;

struct Entry {
    std::string name = "";
    int number = 0;
};

std::vector<int> read_ints(std::istream& is)
{
    std::vector<int> res;

    // If we debug this code with an input "5 10 15\n",
    // we will see we get first to the std::cout line with i=5,
    // and then loop another two times with i=10 and i=15 respectively,
    // just before waiting for some more input at the std::cin line
    //
    // If we then input "hello" we will go out of the loop

    std::cout << "Please input a list of integers ('quit' to finish):\n";
    for (int i; is >> i; )
    {
        res.push_back(i);
    }
    if (is.eof())  // fine: end of file
    {
        std::cout << "EOF reached\n";
        return res;
    }
    if (is.fail())  // we failed to read an int: was it the 'quit' string?
    {
        is.clear();  // reset the state to good
        // Error: this is not necessary
        // Because the first non-int input was not consumed by the stream
        //is.unget();  // put the non-digit back into the stream
        std::string s;
        if (is >> s && s == "quit")
        {
            std::cout << "Exiting correctly\n";
            return res;
        }
        std::cout << "Exiting with an error. User typed: " << s << "\n";
        is.setstate(std::ios_base::failbit);  // add fail() to stream's state
    }
    return res;
}

std::ostream& operator<<(std::ostream& os, const Entry& ee)
{
    return os << "{\"" << ee.name << "\", " << ee.number << "}";
}

std::istream& operator>>(std::istream& is, Entry& ee)
{
    is.clear();
    if (std::streamsize n = is.rdbuf()->in_avail())  // ignores whatever there may be within is
    {
        is.ignore(n);
    }

    std::string line;
    if (std::getline(is, line))
    {
        // \s*{\s*"[A-Za-z][ A-Za-z]*"\s*,\s*\d+\s*}
        // E.g.:
        //    {   "John Malkovich"   ,   555234   }
        // {"Peter Townsend", 777889345}
        // {"A fish called Wanda", 9991}
        std::regex pattern{ R"([[:s:]]*\{[[:s:]]*\"([[:alpha:]][ [:alpha:]]*)\"[[:s:]]*,[[:s:]]*([[:digit:]]+)[[:s:]]*\})" };
        std::smatch matches;
        if (std::regex_search(line, matches, pattern))
        {
            ee = { matches[1], stoi(matches[2]) };
            return is;
        }
    }
    is.setstate(std::ios_base::failbit);
    return is;
}

export void istreams_main()
{
    // Read ints
    auto v = read_ints(std::cin);
    bool first = true;
    std::cout << "List of integers input by the user: " << std::dec;
    std::for_each(v.begin(), v.end(), [&first](int n) { std::cout << (first ? "" : " ") << n; first = false; });
    std::cout << "\n\n";

    // Read entries
    std::cout << "Please input a list of entries, e.g.: {\"John Malkovich\", 555234} ('quit' to finish):\n";
    for (Entry ee; std::cin >> ee; )
    {
        std::cout << "Entry input by the user: " << ee << "\n";
    }
}
