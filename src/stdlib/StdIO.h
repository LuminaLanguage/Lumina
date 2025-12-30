#pragma once
#include <string>

class StdIO {
public:
    static void print(const std::string& msg);
    static std::string input(const std::string& prompt);
};
