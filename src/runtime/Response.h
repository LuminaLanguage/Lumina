#pragma once
#include <string>

class Response {
public:
    int status = 200;
    std::string body;
    void send(const std::string& data) { body = data; }
};
