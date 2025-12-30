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
    void json(const std::string& data) { body = data; }
};

class WebServer {
private:
    crow::SimpleApp app;
    std::vector<std::function<void(Request&, Response&)>> middlewares;

    void handleRoute(const crow::request& req_crow, std::function<void(Request&, Response&)> fn, const std::string& method);

public:
    void listen(int port);
    void use(std::function<void(Request&, Response&)> fn);
    void get(const std::string& path, std::function<void(Request&, Response&)> fn);
    void post(const std::string& path, std::function<void(Request&, Response&)> fn);
    void put(const std::string& path, std::function<void(Request&, Response&)> fn);
    void patch(const std::string& path, std::function<void(Request&, Response&)> fn);
    void options(const std::string& path, std::function<void(Request&, Response&)> fn);
    void del(const std::string& path, std::function<void(Request&, Response&)> fn);
    void head(const std::string& path, std::function<void(Request&, Response&)> fn);
};
