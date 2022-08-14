//
// Created by b0n3 on 8/12/22.
//

#ifndef VEEZEN2RTMP_WEBSOCKETSERVER_H
#define VEEZEN2RTMP_WEBSOCKETSERVER_H

#include <thread>
#include <set>
#include "Server.h"
#include "WebsocketContext.h"
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <Client.h>
#include <yarpl/flowable/Flowable.h>
#include "types.h"


using websocketpp::connection_hdl;
//using websocketpp::lib::placeholders::_1;
//using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

namespace veezen {

class WebSocketServer : public veezen::Server{
private:
    // @Todo: create connection to
    std::thread serverThread;
//    std::shared_ptr<server_t> server;
//    std::shared_ptr<con_list> connections;


    int port;
public:
    ~WebSocketServer() override;
    WebSocketServer(int port): port(port){
        WebSocketServer::setUp();
    };
    void setUp() override;
    void start() override;
    void stop() override;
};

};
#endif //VEEZEN2RTMP_WEBSOCKETSERVER_H
