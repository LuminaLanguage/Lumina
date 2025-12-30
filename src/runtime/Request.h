#pragma once
#include <string>
#include <map>

class Request {
public:
    std::string path;
    std::string method;
    std::map<std::string, std::string> query;
    std::string body;
};
