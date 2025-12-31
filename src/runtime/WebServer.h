#pragma once
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <iostream>
#include "civetweb.h"

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
    struct mg_context *ctx;
    std::vector<std::function<void(Request&, Response&)>> middlewares;
    std::map<std::string, std::function<void(Request&, Response&)>> routes;

    static int civetHandler(struct mg_connection *conn, void *cbdata);

    void registerRoute(const std::string &path, std::function<void(Request&, Response&)> fn);

public:
    WebServer() : ctx(nullptr) {}

    void listen(int port);
    void stop();

    void use(std::function<void(Request&, Response&)> fn);

    void get(const std::string &path, std::function<void(Request&, Response&)> fn);
    void post(const std::string &path, std::function<void(Request&, Response&)> fn);
    void put(const std::string &path, std::function<void(Request&, Response&)> fn);
    void patch(const std::string &path, std::function<void(Request&, Response&)> fn);
    void del(const std::string &path, std::function<void(Request&, Response&)> fn);
    void options(const std::string &path, std::function<void(Request&, Response&)> fn);
    void head(const std::string &path, std::function<void(Request&, Response&)> fn);
};
