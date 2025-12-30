#pragma once
#include <string>

class Logger {
public:
    static void log(const std::string& msg);
    static void warn(const std::string& msg);
    static void error(const std::string& msg);
};
