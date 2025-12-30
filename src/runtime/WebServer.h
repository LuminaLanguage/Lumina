#pragma once
#include <string>
#include <functional>
#include <map>
#include "Request.h"
#include "Response.h"
#include <crow.h>

class WebServer {
public:
    int port;
    crow::SimpleApp app;

    void listen(int p);
    void on(const std::string& method, const std::string& path,
            std::function<void(Request&, Response&)> callback);
};
