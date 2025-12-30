#pragma once
#include <string>
#include <functional>
#include <vector>
#include <crow.h>

class Request {
public:
    std::string path;
    std::string method;
    std::map<std::string, std::string> query;
    std::string body;
};

class Response {
public:
    int status = 200;
    std::string body;
    void send(const std::string& data) { body = data; }
    void json(const std::string& data) { body = data; } // can parse stringified JSON later
};

class WebServer {
private:
    crow::SimpleApp app;
    std::vector<std::function<void(Request&, Response&)>> middlewares;

public:
    void listen(int port);
    void use(std::function<void(Request&, Response&)> fn);
    void get(const std::string& path, std::function<void(Request&, Response&)> fn);
    void post(const std::string& path, std::function<void(Request&, Response&)> fn);
};
