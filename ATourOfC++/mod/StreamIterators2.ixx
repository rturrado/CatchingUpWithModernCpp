export module StreamIterators2;

import <algorithm>;
import <fstream>;
import <iostream>;
import <iterator>;
import <regex>;
import <set>;
import <string>;

export void stream_iterators_2_main()
{
    std::cin.clear();
    if (std::streamsize n = std::cin.rdbuf()->in_avail())  // ignores whatever there may be within std::cin
    {
        std::cin.ignore(n);
    }

    std::string from, to;  // get source and target file names
    std::cout << "Please input source file name (hint: stream_iterators_input.txt): ";
    std::cin >> from;
    std::cout << "And target file name (hint: foo.txt): ";
    std::cin >> to;

    std::ifstream is{ from };  // input stream for file "from"

    std::regex pattern{ R"([[:alpha:]_]+)" };
    std::string str(std::istreambuf_iterator<char>{is}, {});
    std::sregex_iterator ii{ str.begin(), str.end(), pattern };  // input iterator for stream
    std::sregex_iterator eos{};  // input sentinel

    std::ofstream os{ to };  // output stream for file "to"
    std::ostream_iterator<std::string> oo{ os, "\n" };  // output iterator for stream

    std::set<std::string> b;  // collect strings from input
    for (; ii != eos; ++ii)
    {
        b.insert((*ii)[0]);
    }
    std::copy(b.begin(), b.end(), oo);  // copy buffer to output

    if (!is.eof())  // check error states
    {
        std::cout << "Error: !is.eof()\n";
    }
    if (!os)
    {
        std::cout << "Error: !os\n";
    }
}
