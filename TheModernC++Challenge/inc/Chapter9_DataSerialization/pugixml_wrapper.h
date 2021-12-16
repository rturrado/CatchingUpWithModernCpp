#ifndef PUGIXML_WRAPPER_H
#define PUGIXML_WRAPPER_H

#include "pugixml.hpp"

#include <cstddef>  // ptrdiff_t
#include <sstream>  // ostringstream
#include <stdexcept>  // runtime_error
#include <string>

namespace rtc::pugixml
{
    // Runtime errors
    struct AttributeError : public std::runtime_error
    {
        AttributeError(const std::string& name) : std::runtime_error{ message_ + name } {}
    private:
        static inline std::string message_{ "trying to access attribute " };
    };

    struct ChildError : public std::runtime_error
    {
        ChildError(const std::string& name) : std::runtime_error{ message_ + name } {}
    private:
        static inline std::string message_{ "trying to access child " };
    };

    struct AppendAttributeError : public std::runtime_error
    {
        AppendAttributeError(const std::string& name) : std::runtime_error{ message_ + name } {}
    private:
        static inline std::string message_{ "trying to append attribute " };
    };

    struct AppendChildError : public std::runtime_error
    {
        AppendChildError(const std::string& name) : std::runtime_error{ message_ + name } {}
    private:
        static inline std::string message_{ "trying to append child " };
    };

    struct LoadFromError : public std::runtime_error
    {
        LoadFromError(const std::string& description, std::ptrdiff_t offset) : std::runtime_error{ "" }
        {
            std::ostringstream oss{};
            oss << "trying to load from: \"" << description << "\", at offset " << offset;
            message_ = oss.str();
        }
        virtual const char* what() const noexcept override { return message_.c_str(); }
    private:
        static inline std::string message_{};
    };


    // pugixml function wrappers
    inline auto attribute_or_throw(const pugi::xml_node& node, const char* name)
    {
        if (auto ret{ node.attribute(name) }) { return ret; }
        else { throw AttributeError{ name }; }
    }

    inline auto child_or_throw(const pugi::xml_node& node, const char* name)
    {
        if (auto ret{ node.child(name) }) { return ret; }
        else { throw ChildError{ name }; }
    }

    inline auto append_attribute_or_throw(pugi::xml_node& node, const char* name)
    {
        auto ret{ node.append_attribute(name) };
        if (ret) { return ret; }
        else { throw AppendAttributeError{ name }; }
    }

    inline auto append_child_or_throw(pugi::xml_node& root, const char* name)
    {
        auto ret{ root.append_child(name) };
        if (ret) { return ret; }
        else { throw AppendChildError{ name }; }
    }

    inline void load_file_or_throw(pugi::xml_document& doc, const char* path)
    {
        auto result{ doc.load_file(path) };
        if (not result) { throw LoadFromError{ result.description(), result.offset }; }
    }
}  // namespace rtc::pugixml

#endif  // PUGIXML_WRAPPER_H
