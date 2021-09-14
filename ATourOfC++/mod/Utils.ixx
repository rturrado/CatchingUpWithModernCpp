export module Utils;

import <iostream>;
import <sstream>;
import <string>;
import <vector>;

export
{

    template<typename T>
    constexpr void PrintDeclarationAndType(std::string text, T var)
    {
        std::cout << text << typeid(var).name() << "\n";
    }

    template<typename T>
    inline constexpr std::string GetDeclarationAndTypeStr(std::string text, T var)
    {
        std::ostringstream ss;
        ss << text << typeid(var).name() << "\n";
        return ss.str();
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const std::initializer_list<T>& l)
    {
        os << "{";
        bool first = true;
        for (auto& d : l)
        {
            os << (first ? " " : ", ") << d;
            first = false;
        }
        os << " }";
        return os;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
    {
        os << "{";
        bool first = true;
        for (const auto& d : v)
        {
            os << (first ? " " : ", ") << d;
            first = false;
        }
        os << " }";
        return os;
    }

    std::vector<int> read_vector_of_numbers_from_istream(std::istream& is)
    {
        std::vector<int> v;
        std::cout << "Please input a list of numbers ('quit' to finish):\n";
        for (std::string s; is >> s;)
        {
            if (s == "quit")
            {
                break;
            }
            try {
                v.push_back(std::stoi(s));
            }
            catch (const std::invalid_argument&)
            {
                std::cout << s << " is not a number. Please retry.\n";
            }
        }
        return v;  // move constructor
    }

    std::vector<std::string> read_vector_of_strings_from_istream(std::istream& is)
    {
        std::vector<std::string> v;
        std::cout << "Please input a list of strings ('quit' to finish):\n";
        for (std::string s; is >> s; )
        {
            if (s == "quit")
            {
                break;
            }
            v.push_back(s);
        }
        return v;  // move constructor
    }

}  // export
