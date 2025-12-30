#include "Logger.h"
#include <iostream>

void Logger::log(const std::string& msg) { std::cout << "[LOG] " << msg << std::endl; }
void Logger::warn(const std::string& msg) { std::cout << "[WARN] " << msg << std::endl; }
void Logger::error(const std::string& msg) { std::cerr << "[ERROR] " << msg << std::endl; }
