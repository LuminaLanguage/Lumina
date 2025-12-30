#include "WebServer.h"
#include <iostream>

void WebServer::listen(int p) {
    port = p;
    std::cout << "Server listening on port " << port << std::endl;
}

void WebServer::on(const std::string& method, const std::string& path, std::function<void(Request&, Response&)> callback) {
    routes[method + ":" + path] = callback;
}
