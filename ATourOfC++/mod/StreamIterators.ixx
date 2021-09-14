export module StreamIterators;

import <algorithm>;
import <fstream>;
import <iostream>;
import <set>;
import <string>;
import <vector>;

export void stream_iterators_main()
{
    std::cin.clear();
    if (std::streamsize n = std::cin.rdbuf()->in_avail())  // ignores whatever there may be within std::cin
    {
        std::cin.ignore(n);
    }

    std::string from, to;  // get source and target file names
    std::cout << "Please input source file name (hint: stream_iterators_input.txt): ";
    std::cin >> from;
    std::cout << "And target file name (hint: blah.txt): ";
    std::cin >> to;

    std::ifstream is{ from };  // input stream for file "from"
    std::istream_iterator<std::string> ii{ is };  // input iterator for stream
    std::istream_iterator<std::string> eos{};  // input sentinel

    std::ofstream os{ to };  // output stream for file "to"
    std::ostream_iterator<std::string> oo{ os, "\n" };  // output iterator for stream

    //std::vector<std::string> b{ ii, eos };  // b is a vector initialized from input
    //sort(b.begin(), b.end());  // sort the buffer
    //unique_copy(b.begin(), b.end(), oo);  // copy buffer to output, discard replicated values

    std::set<std::string> b{ ii, eos };  // collect strings from input
    std::copy(b.begin(), b.end(), oo);  // copy buffer to output

    if (!is.eof())  // check error states
    {
        std::cout << "Error: !is.eof()";
    }
    if (!os)
    {
        std::cout << "Error: !os";
    }
}
