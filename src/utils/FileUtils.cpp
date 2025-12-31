#include "./FileUtils.h"
#include <fstream>
#include <sstream>

std::string FileUtils::readFile(const std::string& path) {
    std::ifstream file(path);
    if(!file.is_open()) return "";
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void FileUtils::writeFile(const std::string& path, const std::string& data) {
    std::ofstream file(path);
    file << data;
}
