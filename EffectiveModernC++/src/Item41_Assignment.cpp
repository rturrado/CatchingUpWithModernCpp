#include "Item41_Assignment.h"

#include <cstdlib>  // malloc, free
#include <cstring>  // strlen
#include <iostream>  // cout
#include <string>
#include <utility>  // exchange, move


namespace item_41_assignment
{
    class String
    {
    public:
        String()
        {
            std::cout << "\t\tString()\n";
        }
        String(const char* cstr)
            : data_{ nullptr }
        {
            std::cout << "\t\tString(const char* str)\n";
            data_ = copy_data(cstr);
        }
        String(const std::string& str)
            : data_{ nullptr }
        {
            std::cout << "\t\tString(const std::string& str)\n";
            data_ = copy_data(str.c_str());
        }
        String(const String& other)
            : data_{ nullptr }
        {
            std::cout << "\t\tString(const String& other)\n";
            data_ = copy_data(other.data_);
        }
        String(String&& other)
            : data_{ nullptr }
        {
            std::cout << "\t\tString(String&& other)\n";
            data_ = move_data(other.data_);
            other.data_ = nullptr;
        }
        String& operator=(const String& other)
        {
            std::cout << "\t\tString& operator=(const String& other)\n";
            data_ = copy_data(other.data_);
            return *this;
        }
        String& operator=(String&& other)
        {
            std::cout << "\t\tString& operator=(String&& other)\n";
            data_ = move_data(other.data_);
            other.data_ = nullptr;
            return *this;
        }
        ~String()
        {
            std::cout << "\t\t~String()\n";
            delete_data(data_);
        };

        char* copy_data(const char* other)
        {
            size_t size{ strlen(other) + 1 };
            if (data_ and strlen(data_)) { delete_data(data_); }
            data_ = static_cast<char*>(new_data(size));
            strcpy_s(data_, size, other);
            return data_;
        }
        char* move_data(char* other)
        {
            char* current_str{ std::exchange(data_, other) };
            delete_data(current_str);
            return data_;
        }
        void* new_data(size_t size)
        {
            void* ret{ malloc(size) };
            std::cout << "\t\t\t---- new(" << size << ") -> 0x" << std::hex << ret << std::dec << "\n";
            return ret;
        }
        void delete_data(void* data)
        {
            if (data)
            {
                size_t size{ strlen(static_cast<char*>(data)) + 1 };
                std::cout << "\t\t\t---- delete(" << size << ") -> 0x" << std::hex << data << std::dec << "\n";
                free(data);
            }
            else
            {
                std::cout << "\t\t\t---- delete(0) -> 0x00000000\n";
            }
        }

    private:
        char* data_{ nullptr };
    };

    class Password
    {
    public:
        Password() = default;
        explicit Password(String pw) : password_{ std::move(pw) } {}
        void changeToByValue(String pw) { password_ = std::move(pw); }
        void changeToByLvalueReference(const String& pw) { password_ = pw; }
        void changeToByRvalueReference(String&& pw) { password_ = std::move(pw); }
        template <typename T>
        void changeToByUniversalReference(T&& pw) { password_ = std::forward<T>(pw); }

    private:
        String password_{};
    };
}  // namespace item_41_assignment


void item_41_assignment_main()
{
    using namespace item_41_assignment;

    std::cout << "String yellow_bananas{\"Bananas are yellow\"}:\n"; String yellow_bananas{ "Bananas are yellow" };
    {
        std::cout << "* changeToByValue:\n";
        std::cout << "\tPassword pw{ \"I will not forget this password again\" }\n"; Password pw{ "I will not forget this password again" };
        std::cout << "\tchangeToByValue(yellow_bananas):\n"; pw.changeToByValue(yellow_bananas);
    }
    {
        std::cout << "* changeToByLvalueReference:\n";
        std::cout << "\tPassword pw{ \"I will not forget this password again\" }\n"; Password pw{ "I will not forget this password again" };
        std::cout << "\tchangeToByLvalueReference(yellow_bananas):\n"; pw.changeToByLvalueReference(yellow_bananas);
    }
    {
        std::cout << "* changeToByRvalueReference:\n";
        std::cout << "\tPassword pw{ \"I will not forget this password again\" }\n"; Password pw{ "I will not forget this password again" };
        std::cout << "\tchangeToByRvalueReference(\"Bananas are green\"):\n"; pw.changeToByRvalueReference("Bananas are green");
    }
    {
        std::cout << "* changeToByUniversalReference (lvalue):\n";
        std::cout << "\tPassword pw{ \"I will not forget this password again\" }\n"; Password pw{ "I will not forget this password again" };
        std::cout << "\tchangeToByUniversalReference(yellow_bananas):\n"; pw.changeToByUniversalReference(yellow_bananas);
    }
    {
        std::cout << "* changeToByUniversalReference (rvalue):\n";
        std::cout << "\tPassword pw{ \"I will not forget this password again\" }\n"; Password pw{ "I will not forget this password again" };
        std::cout << "\tchangeToByUniversalReference(\"Bananas are green\"):\n"; pw.changeToByUniversalReference("Bananas are green");
    }

    std::cout << "+ Exiting\n";
}
