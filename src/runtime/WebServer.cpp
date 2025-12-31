#include "runtime/WebServer.h"
#include <cstring>
#include <iostream>

// Internal CivetWeb handler for all routes
int WebServer::civetHandler(struct mg_connection *conn, void *cbdata) {
    WebServer* self = static_cast<WebServer*>(cbdata);

    mg_request_info *req_info = mg_get_request_info(conn);

    // Read request body
    char buf[1024];
    int n = mg_read(conn, buf, sizeof(buf));
    std::string body;
    if (n > 0) body.assign(buf, n);

    Request req;
    Response res;

    req.path = req_info->request_uri;
    req.method = req_info->request_method;
    req.body = body;

    // Run middlewares
    for (auto& mw : self->middlewares) mw(req, res);

    // Call route handler if exists
    auto it = self->routes.find(req.path);
    if (it != self->routes.end()) {
        it->second(req, res);
    }

    // Send response
    mg_printf(conn,
        "HTTP/1.1 %d OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: %zu\r\n\r\n%s",
        res.status, res.body.size(), res.body.c_str());

    return 1; // Mark handled
}

// Listen on a port
void WebServer::listen(int port) {
    std::string portStr = std::to_string(port);
    const char *options[] = {
        "listening_ports", portStr.c_str(),
        nullptr
    };

    ctx = mg_start(nullptr, this, options);

    if (!ctx) {
        std::cerr << "Failed to start server on port " << port << std::endl;
    }
}

// Add middleware
void WebServer::use(std::function<void(Request&, Response&)> fn) {
    middlewares.push_back(fn);
}

// Generic route registration
void WebServer::registerRoute(const std::string &path, std::function<void(Request&, Response&)> fn) {
    routes[path] = fn;
}

// GET route
void WebServer::get(const std::string &path, std::function<void(Request&, Response&)> fn) {
    registerRoute(path, fn);
}

// POST route
void WebServer::post(const std::string &path, std::function<void(Request&, Response&)> fn) {
    registerRoute(path, fn);
}

// PUT route
void WebServer::put(const std::string &path, std::function<void(Request&, Response&)> fn) {
    registerRoute(path, fn);
}

// PATCH route
void WebServer::patch(const std::string &path, std::function<void(Request&, Response&)> fn) {
    registerRoute(path, fn);
}

// DELETE route
void WebServer::del(const std::string &path, std::function<void(Request&, Response&)> fn) {
    registerRoute(path, fn);
}

// OPTIONS route
void WebServer::options(const std::string &path, std::function<void(Request&, Response&)> fn) {
    registerRoute(path, fn);
}

// HEAD route (simulate via GET, empty body)
void WebServer::head(const std::string &path, std::function<void(Request&, Response&)> fn) {
    registerRoute(path, [fn](Request &req, Response &res) {
        fn(req, res);
        res.body = ""; // HEAD returns no body
    });
}
