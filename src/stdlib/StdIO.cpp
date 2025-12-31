#include "stdlib/StdIO.h"
#include <iostream>

void StdIO::print(const std::string& msg) { std::cout << msg << std::endl; }

std::string StdIO::input(const std::string& prompt) {
    std::cout << prompt;
    std::string val;
    std::getline(std::cin, val);
    return val;
}
