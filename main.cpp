
#include <thread>

#include <folly/init/Init.h>
#include <folly/portability/GFlags.h>
//#include "./src/rsocket_implementation/include/VeeRsocketServer.h"
#include <thread>
#include "src/websocket_implementation/includes/WebSocketServer.h"

DEFINE_int32(port, 9898, "port to connect to");

int main(int argc, char **argv) {
//    FLAGS_logtostderr = true;
//    FLAGS_minloglevel = 0;

    folly::init(&argc, &argv);
    auto server = std::make_shared<veezen::WebSocketServer>(8080);

    server->start();
//auto rsocketServer = std::make_shared<veezen::VeeRsocketServer>("::", FLAGS_port, 2);
//        rsocketServer->start();
    // @todo: luanch  all other listners herer
    std::getchar();
//    rsocketServer->stop();
    server->stop();

    return 0;
}
