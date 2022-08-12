//
// Created by b0n3 on 8/12/22.
//

#ifndef VEEZEN2RTMP_WEBSOCKETSERVER_H
#define VEEZEN2RTMP_WEBSOCKETSERVER_H

#include <thread>
#include <set>
#include "Server.h"
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <Client.h>
#include <yarpl/flowable/Flowable.h>



using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

typedef websocketpp::server<websocketpp::config::asio> server_t;
typedef std::string TOKEN;
using websocketpp::connection_hdl;

typedef std::shared_ptr<yarpl::flowable::Flowable<server_t::message_ptr>> STREAM;
typedef std::map<connection_hdl,veezen::Client<STREAM, STREAM, TOKEN>,
        std::owner_less<connection_hdl>> con_list;

namespace veezen {

class WebSocketServer : public veezen::Server{
private:
    std::thread serverThread;
    std::shared_ptr<server_t> server;
    std::shared_ptr<con_list> connections;
    int port;
public:
    WebSocketServer(int port): port(port){
        WebSocketServer::setUp();
    };
    void setUp() override;
    void on_open(connection_hdl hdl);
    void on_close(connection_hdl hdl);
    void on_message(std::shared_ptr<server_t> s,
                    connection_hdl hdl,
                    server_t::message_ptr msg);
    void start() override;

    void stop() override;
};

};
#endif //VEEZEN2RTMP_WEBSOCKETSERVER_H
