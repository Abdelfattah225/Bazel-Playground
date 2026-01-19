// utils/string_helper.cpp
#include "string_helper.hpp"
#include <algorithm>
#include <cctype>

bool StringHelper::isEmpty(const std::string& s) {
    return s.empty();
}

int StringHelper::length(const std::string& s) {
    return s.length();
}

std::string StringHelper::toUpper(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}