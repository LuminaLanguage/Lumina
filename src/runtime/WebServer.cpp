#include "runtime/WebServer.h"

void WebServer::listen(int port) {
    app.port(port).multithreaded().run();
}

void WebServer::use(std::function<void(Request&, Response&)> fn) {
    middlewares.push_back(fn);
}

void WebServer::handleRoute(const crow::request& req_crow, std::function<void(Request&, Response&)> fn, const std::string& method) {
    Request req;
    Response res;
    req.method = method;
    req.path = req_crow.url;
    req.body = req_crow.body;

    for(auto& mw : middlewares) mw(req, res);
    fn(req, res);
}

// GET
void WebServer::get(const std::string& path, std::function<void(Request&, Response&)> fn) {
    CROW_ROUTE(app, path)([this, fn](const crow::request& req_crow){ handleRoute(req_crow, fn, "GET"); return ""; });
}

// POST
void WebServer::post(const std::string& path, std::function<void(Request&, Response&)> fn) {
    CROW_ROUTE(app, path).methods(crow::HTTPMethod::Post)([this, fn](const crow::request& req_crow){ handleRoute(req_crow, fn, "POST"); return ""; });
}

// PUT
void WebServer::put(const std::string& path, std::function<void(Request&, Response&)> fn) {
    CROW_ROUTE(app, path).methods(crow::HTTPMethod::Put)([this, fn](const crow::request& req_crow){ handleRoute(req_crow, fn, "PUT"); return ""; });
}

// PATCH
void WebServer::patch(const std::string& path, std::function<void(Request&, Response&)> fn) {
    CROW_ROUTE(app, path).methods(crow::HTTPMethod::Patch)([this, fn](const crow::request& req_crow){ handleRoute(req_crow, fn, "PATCH"); return ""; });
}

// OPTIONS
void WebServer::options(const std::string& path, std::function<void(Request&, Response&)> fn) {
    CROW_ROUTE(app, path).methods(crow::HTTPMethod::Options)([this, fn](const crow::request& req_crow){ handleRoute(req_crow, fn, "OPTIONS"); return ""; });
}

// DELETE
void WebServer::del(const std::string& path, std::function<void(Request&, Response&)> fn) {
    CROW_ROUTE(app, path).methods(crow::HTTPMethod::Delete)([this, fn](const crow::request& req_crow){ handleRoute(req_crow, fn, "DELETE"); return ""; });
}

// HEAD
void WebServer::head(const std::string& path, std::function<void(Request&, Response&)> fn) {
    CROW_ROUTE(app, path).methods(crow::HTTPMethod::Head)([this, fn](const crow::request& req_crow){ handleRoute(req_crow, fn, "HEAD"); return ""; });
}
