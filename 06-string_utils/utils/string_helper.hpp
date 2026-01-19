// utils/string_helper.hpp
#ifndef STRING_HELPER_HPP
#define STRING_HELPER_HPP

#include <string>

class StringHelper {
public:
    bool isEmpty(const std::string& s);
    int length(const std::string& s);
    std::string toUpper(const std::string& s);
};

#endif