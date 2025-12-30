#pragma once
#include <string>
#include <functional>
#include <map>
#include "../runtime/Request.h"
#include "../runtime/Response.h"

class WebServer {
public:
    int port;
    std::map<std::string, std::function<void(Request&, Response&)>> routes;
    void listen(int p);
    void on(const std::string& method, const std::string& path, std::function<void(Request&, Response&)> callback);
};
