#pragma once
#include <string>
#include <vector>

class StringUtils {
public:
    static std::vector<std::string> split(const std::string& str, char delim);
    static std::string trim(const std::string& str);
};
