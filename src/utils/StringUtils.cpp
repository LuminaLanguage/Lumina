#include "./StringUtils.h"
#include <sstream>

std::vector<std::string> StringUtils::split(const std::string& str, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;
    while(std::getline(ss, item, delim)) result.push_back(item);
    return result;
}

std::string StringUtils::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if(first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last-first+1);
}
