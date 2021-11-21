#include "Item41_Constructors.h"

#include <iostream>  // cout
#include <string>
#include <utility>  // move
#include <vector>


namespace item_41_constructors
{
    class String
    {
    public:
        String() { std::cout << "\tString()\n"; }
        String(const char* cstr) : str_{ cstr } { std::cout << "\tString(const char* str)\n"; }
        String(const std::string& str) : str_{ str } { std::cout << "\tString(const std::string& str)\n"; }
        String(const String& other) : str_{ other.str_ } { std::cout << "\tString(const String& other)\n"; }
        String(String&& other) : str_{ std::move(other.str_) } { std::cout << "\tString(String&& other)\n"; }
        String& operator=(const String& other)
        {
            str_ = other.str_; std::cout << "\tString& operator=(const String& other)\n"; return *this;
        }
        String& operator=(String&& other)
        {
            str_ = std::move(other.str_); std::cout << "\tString& operator=(String&& other)\n"; return *this;
        }
        ~String() { std::cout << "\t~String()\n"; };

    private:
        std::string str_{};
    };

    class Widget
    {
    public:
        void addNameByValue(String name) { names_.push_back(std::move(name)); }
        void addNameByLvalueReference(const String& name) { names_.push_back(name); }
        void addNameByRvalueReference(String&& name) { names_.push_back(std::move(name)); }
        template <typename T>
        void addNameByUniversalReference(T&& name) { names_.push_back(std::forward<T>(name)); }
    private:
        std::vector<String> names_{};
    };
}  // namespace item_41_constructors


void item_41_constructors_main()
{
    using namespace item_41_constructors;

    std::cout << "* String john{\"John\"}:\n"; const String john{ "John" };
    { Widget w{}; std::cout << "* addNameByValue:\n"; w.addNameByValue(john); }
    { Widget w{}; std::cout << "* addNameByLvalueReference:\n"; w.addNameByLvalueReference(john); }
    { Widget w{}; std::cout << "* addNameByRvalueReference:\n"; w.addNameByRvalueReference(String{ "Maria" }); }
    { Widget w{}; std::cout << "* addNameByUniversalReference (lvalue):\n"; w.addNameByUniversalReference(john); }
    { Widget w{}; std::cout << "* addNameByUniversalReference (rvalue):\n"; w.addNameByUniversalReference(String{ "Maria" }); }

    std::cout << "* Exiting\n";
}
