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
        void addNameByValue(String name) { std::cout << "\tBefore names_.push_back(std::move(name))\n"; names_.push_back(std::move(name)); }
        void addNameByLvalueReference(const String& name) { std::cout << "\tBefore names_.push_back(name)\n"; names_.push_back(name); }
        void addNameByRvalueReference(String&& name) { std::cout << "\tBefore names_.push_back(std::move(name))\n"; names_.push_back(std::move(name)); }
        template <typename T>
        void addNameByUniversalReference(T&& name) { std::cout << "\tBefore names_.push_back(std::forward<T>(name))\n"; names_.push_back(std::forward<T>(name)); }
    private:
        std::vector<String> names_{};
    };
}  // namespace item_41_constructors


// Item 41 talks about considering pass by value for copyable parameters that are cheap to move and always copied
// When all of that applies, pass by value may be preferable to a) overloading, and b) using universal references
//
// - Overloading:
//   - requires implementing two functions that do essentially the same thing, one for lvalue references and one for rvalue references
//   - furthermore, there will be two functions in object code
//
// - Using universal references also leads to some complications:
//   - implementation in header file,
//   - several functions in objet code,
//   - argument types that can't be passed,
//   - intimidating compiler error messages when clients pass improper argument types
//
// The cost of passing by value, compared to the other options, should be one extra move
//
// Widget implements different functions in order to allow testing of pass by value, overloading, and using universal references
// All those functions have a String parameter that is pushed back into a vector
// String is a class that just holds a std::string and prints whenever an object of type String is constructed, destructed or assigned
void item_41_constructors_main()
{
    using namespace item_41_constructors;

    std::cout << "String john{\"John\"}:\n"; const String john{ "John" };

    { Widget w{}; std::cout << "addNameByValue (lvalue):\n"; w.addNameByValue(john); }  // 1 copy, 1 move
    { Widget w{}; std::cout << "addNameByLvalueReference:\n"; w.addNameByLvalueReference(john); }  // 1 copy
    { Widget w{}; std::cout << "addNameByUniversalReference (lvalue):\n"; w.addNameByUniversalReference(john); }  // 1 copy

    { Widget w{}; std::cout << "addNameByValue (rvalue):\n"; String maria{ "Maria" }; w.addNameByValue(std::move(maria)); }  // 2 moves
    { Widget w{}; std::cout << "addNameByRvalueReference:\n"; String maria{ "Maria" }; w.addNameByRvalueReference(std::move(maria)); }  // 1 move
    { Widget w{}; std::cout << "addNameByUniversalReference (rvalue):\n"; String maria{ "Maria" }; w.addNameByUniversalReference(std::move(maria)); }  // 1 move

    std::cout << "Exiting\n";
}
