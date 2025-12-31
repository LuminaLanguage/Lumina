#pragma once
#include <string>
#include <functional>
#include <vector>
#include <map>
#include "civetweb.h"  // CivetWeb header

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

    // Internal route handler
    static int routeHandler(struct mg_connection *conn, void *cbdata) {
        WebServer *self = static_cast<WebServer*>(cbdata);

        char buf[1024];
        int n = mg_read(conn, buf, sizeof(buf));
        std::string body;
        if (n > 0) body.assign(buf, n);

        mg_request_info *req_info = mg_get_request_info(conn);

        Request req;
        Response res;
        req.path = req_info->request_uri;
        req.method = req_info->request_method;
        req.body = body;

        for (auto &mw : self->middlewares) mw(req, res);

        // Send response
        mg_printf(conn,
                  "HTTP/1.1 %d OK\r\n"
                  "Content-Type: text/plain\r\n"
                  "Content-Length: %zu\r\n\r\n%s",
                  res.status, res.body.size(), res.body.c_str());

        return 1; // Mark handled
    }

public:
    WebServer() : ctx(nullptr) {}

    void listen(int port) {
        const char *options[] = {
            "listening_ports", std::to_string(port).c_str(),
            nullptr
        };
        ctx = mg_start(nullptr, this, options);
    }

    void stop() {
        if (ctx) mg_stop(ctx);
        ctx = nullptr;
    }

    void use(std::function<void(Request&, Response&)> fn) {
        middlewares.push_back(fn);
    }

    void get(const std::string &path, std::function<void(Request&, Response&)> fn) {
        mg_set_request_handler(ctx, path.c_str(), routeHandler, this);
    }

    void post(const std::string &path, std::function<void(Request&, Response&)> fn) {
        mg_set_request_handler(ctx, path.c_str(), routeHandler, this);
    }

    void put(const std::string &path, std::function<void(Request&, Response&)> fn) {
        mg_set_request_handler(ctx, path.c_str(), routeHandler, this);
    }

    void patch(const std::string &path, std::function<void(Request&, Response&)> fn) {
        mg_set_request_handler(ctx, path.c_str(), routeHandler, this);
    }

    void del(const std::string &path, std::function<void(Request&, Response&)> fn) {
        mg_set_request_handler(ctx, path.c_str(), routeHandler, this);
    }

    void options(const std::string &path, std::function<void(Request&, Response&)> fn) {
        mg_set_request_handler(ctx, path.c_str(), routeHandler, this);
    }

    // CivetWeb does not support HEAD directly; you can implement it via GET
    void head(const std::string &path, std::function<void(Request&, Response&)> fn) {
        mg_set_request_handler(ctx, path.c_str(), routeHandler, this);
    }
};
