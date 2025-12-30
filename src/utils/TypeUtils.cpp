#include "TypeUtils.h"
#include <cctype>

bool TypeUtils::isNumber(const std::string& val) {
    for(char c : val) if(!isdigit(c) && c != '.') return false;
    return !val.empty();
}

bool TypeUtils::isString(const std::string& val) { return !isNumber(val); }
