#include "./StdWeb.h"

WebServer StdWeb::createServer(int port) {
    WebServer ws;
    ws.listen(port);
    return ws;
}
