#pragma once
#include <string>
#include <functional>
#include <vector>
#include <map>
#include "httplib.h"  // cpp-httplib

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
    void json(const std::string& data) { body = data; }  // keep same as Crow version
};

class WebServer {
private:
    httplib::Server server;
    std::vector<std::function<void(Request&, Response&)>> middlewares;

    void handleRoute(const httplib::Request& req_ht, httplib::Response& res_ht,
                     std::function<void(Request&, Response&)> fn,
                     const std::string& method) 
    {
        Request req;
        Response res;

        req.path = req_ht.path;
        req.method = method;
        req.body = req_ht.body;

        for (auto& mw : middlewares) mw(req, res);
        fn(req, res);

        res_ht.status = res.status;
        res_ht.set_content(res.body, "text/plain");
    }

public:
    void listen(int port) {
        server.listen("0.0.0.0", port);
    }

    void use(std::function<void(Request&, Response&)> fn) {
        middlewares.push_back(fn);
    }

    void get(const std::string& path, std::function<void(Request&, Response&)> fn) {
        server.Get(path.c_str(), [this, fn](const httplib::Request& req, httplib::Response& res){
            handleRoute(req, res, fn, "GET");
        });
    }

    void post(const std::string& path, std::function<void(Request&, Response&)> fn) {
        server.Post(path.c_str(), [this, fn](const httplib::Request& req, httplib::Response& res){
            handleRoute(req, res, fn, "POST");
        });
    }

    void put(const std::string& path, std::function<void(Request&, Response&)> fn) {
        server.Put(path.c_str(), [this, fn](const httplib::Request& req, httplib::Response& res){
            handleRoute(req, res, fn, "PUT");
        });
    }

    void patch(const std::string& path, std::function<void(Request&, Response&)> fn) {
        server.Patch(path.c_str(), [this, fn](const httplib::Request& req, httplib::Response& res){
            handleRoute(req, res, fn, "PATCH");
        });
    }

    void del(const std::string& path, std::function<void(Request&, Response&)> fn) {
        server.Delete(path.c_str(), [this, fn](const httplib::Request& req, httplib::Response& res){
            handleRoute(req, res, fn, "DELETE");
        });
    }

    void options(const std::string& path, std::function<void(Request&, Response&)> fn) {
        server.Options(path.c_str(), [this, fn](const httplib::Request& req, httplib::Response& res){
            handleRoute(req, res, fn, "OPTIONS");
        });
    }

    void head(const std::string& path, std::function<void(Request&, Response&)> fn) {
        server.Head(path.c_str(), [this, fn](const httplib::Request& req, httplib::Response& res){
            handleRoute(req, res, fn, "HEAD");
        });
    }
};
