#pragma once
#include <string>

class TypeUtils {
public:
    static bool isNumber(const std::string& val);
    static bool isString(const std::string& val);
};
