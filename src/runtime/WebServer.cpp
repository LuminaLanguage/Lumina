#include "runtime/WebServer.h"

// Listen on the given port
void WebServer::listen(int port) {
    server.listen("0.0.0.0", port);
}

// Add a middleware function
void WebServer::use(std::function<void(Request&, Response&)> fn) {
    middlewares.push_back(fn);
}

// Handle a route request
void WebServer::handleRoute(const httplib::Request& req_ht, httplib::Response& res_ht,
                            std::function<void(Request&, Response&)> fn,
                            const std::string& method) 
{
    Request req;
    Response res;

    req.path = req_ht.path;
    req.method = method;
    req.body = req_ht.body;

    // Apply middlewares
    for (auto& mw : middlewares) {
        mw(req, res);
    }

    // Call the actual route handler
    fn(req, res);

    // Set response
    res_ht.status = res.status;
    res_ht.set_content(res.body, "text/plain");
}

// GET route
void WebServer::get(const std::string& path, std::function<void(Request&, Response&)> fn) {
    server.Get(path.c_str(), [this, fn](const httplib::Request& req, httplib::Response& res){
        handleRoute(req, res, fn, "GET");
    });
}

// POST route
void WebServer::post(const std::string& path, std::function<void(Request&, Response&)> fn) {
    server.Post(path.c_str(), [this, fn](const httplib::Request& req, httplib::Response& res){
        handleRoute(req, res, fn, "POST");
    });
}

// PUT route
void WebServer::put(const std::string& path, std::function<void(Request&, Response&)> fn) {
    server.Put(path.c_str(), [this, fn](const httplib::Request& req, httplib::Response& res){
        handleRoute(req, res, fn, "PUT");
    });
}

// PATCH route
void WebServer::patch(const std::string& path, std::function<void(Request&, Response&)> fn) {
    server.Patch(path.c_str(), [this, fn](const httplib::Request& req, httplib::Response& res){
        handleRoute(req, res, fn, "PATCH");
    });
}

// DELETE route
void WebServer::del(const std::string& path, std::function<void(Request&, Response&)> fn) {
    server.Delete(path.c_str(), [this, fn](const httplib::Request& req, httplib::Response& res){
        handleRoute(req, res, fn, "DELETE");
    });
}

// OPTIONS route
void WebServer::options(const std::string& path, std::function<void(Request&, Response&)> fn) {
    server.Options(path.c_str(), [this, fn](const httplib::Request& req, httplib::Response& res){
        handleRoute(req, res, fn, "OPTIONS");
    });
}

// HEAD route
void WebServer::head(const std::string& path, std::function<void(Request&, Response&)> fn) {
    server.Head(path.c_str(), [this, fn](const httplib::Request& req, httplib::Response& res){
        handleRoute(req, res, fn, "HEAD");
    });
}
