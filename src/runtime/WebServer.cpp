#include "WebServer.h"

void WebServer::listen(int p) {
    port = p;
    app.port(port).multithreaded().run();
}

void WebServer::on(const std::string& method, const std::string& path,
                   std::function<void(Request&, Response&)> callback) {
    if(method == "GET") {
        CROW_ROUTE(app, path) ([callback](const crow::request& req_crow) {
            Request req;
            Response res;

            req.path = req_crow.url;
            req.method = "GET";
            req.body = req_crow.body;

            callback(req, res);

            return res.body;
        });
    } else if(method == "POST") {
        CROW_ROUTE(app, path).methods(crow::HTTPMethod::Post)
        ([callback](const crow::request& req_crow) {
            Request req;
            Response res;

            req.path = req_crow.url;
            req.method = "POST";
            req.body = req_crow.body;

            callback(req, res);

            return res.body;
        });
    }
}
