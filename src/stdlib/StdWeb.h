#pragma once
#include "../runtime/WebServer.h"

class StdWeb {
public:
    static WebServer createServer(int port);
};
