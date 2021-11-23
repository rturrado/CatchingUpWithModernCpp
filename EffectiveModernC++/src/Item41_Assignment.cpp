#include "Item41_Assignment.h"

#include <cstdlib>  // malloc, free
#include <cstring>  // memcpy, strlen, strcpy_s
#include <format>
#include <iostream>  // cout
#include <string>
#include <utility>  // exchange, move


namespace item_41_assignment
{
    class String
    {
    public:
        String() { std::cout << "\tString()\n"; }
        String(const char* cstr) { std::cout << "\tString(const char* str)\n"; construct_with_str(cstr); }
        String(const std::string& str) { std::cout << "\tString(const std::string& str)\n"; construct_with_str(str.c_str()); }
        String(const String& other) { std::cout << "\tString(const String& other)\n"; copy_data(other); }
        String(String&& other) { std::cout << "\tString(String&& other)\n"; move_data(std::move(other)); }
        String& operator=(const String& other) { std::cout << "\tString& operator=(const String& other)\n"; copy_data(other); return *this; }
        String& operator=(String&& other) { std::cout << "\tString& operator=(String&& other)\n"; move_data(std::move(other)); return *this; }
        ~String() { std::cout << "\t~String()\n"; deallocate_data(data_, size_); data_ = nullptr; size_ = 0; };

        size_t length_str(const char* other)
        {
            return std::strlen(other) + 1;
        }
        void construct_with_str(const char* cstr)
        {
            size_t length{ length_str(cstr) };

            data_ = allocate_data(length);
            size_ = length;

            strcpy_s(static_cast<char*>(data_), length, cstr);
        }
        void copy_data(const String& other)
        {
            // This optimization is required for this example's testing purposes
            // We can avoid an allocation and a deallocation during a copy assignment if the new string is shorter than the current one
            // Otherwise, pass by reference followed by copy assignment would be just as expensive as pass by value followed by move assignment
            if (size_ < other.size_)
            {
                data_ = reallocate_data(other.size_);
                size_ = other.size_;
            }
            else
            {
                std::cout << "\t\tOverwriting current memory buffer with the new data\n";
            }
            std::memcpy(data_, other.data_, size_);
        }
        void move_data(String&& other)
        {
            auto current_data{ std::exchange(data_, other.data_) };
            auto current_size{ size_ }; size_ = other.size_;
            deallocate_data(current_data, current_size);
            other.data_ = nullptr;
            other.size_ = 0;
        }
        void* allocate_data(size_t size)
        {
            void* ret{ malloc(size) };
            std::cout << std::format("\t\t{:p}: new({})\n", ret, size);
            return ret;
        }
        void deallocate_data(void* data, size_t size)
        {
            if (data)
            {
                std::cout << std::format("\t\t{:p}: delete({})\n", data, size);
                free(data);
            }
            else
            {
                std::cout << std::format("\t\t{:p}: delete(0)\n", data);
            }
        }
        void* reallocate_data(size_t size)
        {
            if (data_ and size_)
            {
                deallocate_data(data_, size_);
            }
            return allocate_data(size);
        }

    private:
        void* data_{ nullptr };
        size_t size_{ 0 };
    };

    class Password
    {
    public:
        Password() = default;
        explicit Password(String pw) : password_{ std::move(pw) } {}
        void changeToByValue(String pw) { password_ = std::move(pw); }
        void changeToByLvalueReference(const String& pw) { password_ = pw; }
        template <typename T>
        void changeToByUniversalReference(T&& pw) { password_ = std::forward<T>(pw); }

    private:
        String password_{};
    };
}  // namespace item_41_assignment


// Item 41 talks about considering pass by value for copyable parameters that are cheap to move and always copied
// When all of that applies, pass by value may be preferable to a) overloading, and b) using universal references
//
// However, for lvalue arguments, pass by value followed by move assignment may be significantly more expensive than
// pass by reference followed by copy assignment
//
// The code below tests this special case. It first creates a Password, an object that holds a String, and then changes it
// passing the new text as an lvalue argument in three different ways: by value, as a reference, and as a universal reference
// 
// It is important to notice a few things:
// - String is a class that manages a string of characters in heap memory
// - Every time an allocation or deallocation is done within String, a message is printed out
//   indicating the memory location and the number of bytes of the operation
// - String's copy assignment operator checks if the new string is shorter than the current one and, in that case,
//   it just overwrites the memory buffer where it stores the string
// - The tests always change the current password to a shorter one
void item_41_assignment_main()
{
    using namespace item_41_assignment;

    std::cout << "String yellow_bananas{\"Bananas are yellow\"}:\n";
    String yellow_bananas{ "Bananas are yellow" };  // alloc 19 bytes (constructor)
    {
        std::cout << "Password pw{ \"I will not forget this password again\" }\n";
        Password pw{ "I will not forget this password again" };  // alloc 38 bytes (constructor)
        std::cout << "changeToByValue(yellow_bananas):\n";
        pw.changeToByValue(yellow_bananas);  // alloc 19 bytes (copy constructor), and delete 38 bytes (move assignment)
    }  // 19 bytes (destructor)
    {
        std::cout << "Password pw{ \"I will not forget this password again\" }\n";
        Password pw{ "I will not forget this password again" };  // alloc 38 bytes (constructor)
        std::cout << "changeToByLvalueReference(yellow_bananas):\n";
        pw.changeToByLvalueReference(yellow_bananas);  // copy assignment without realloc, since new data is shorter than current data
    }  // delete 38 bytes (destructor)
    {
        std::cout << "Password pw{ \"I will not forget this password again\" }\n";
        Password pw{ "I will not forget this password again" };  // alloc 38 bytes (constructor)
        std::cout << "changeToByUniversalReference(yellow_bananas):\n";
        pw.changeToByUniversalReference(yellow_bananas);  // copy assignment without realloc, since new data is shorter than current data
    }  // delete 38 bytes (destructor)

    std::cout << "Exiting\n";
}  // delete 19 bytes (destructor)
