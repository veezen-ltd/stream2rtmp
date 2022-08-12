//
// Created by b0n3 on 8/12/22.
//

#include "../includes/WebSocketServer.h"
#include "../includes/WebsocketFrame.h"

void veezen::WebSocketServer::setUp() {
    server = std::make_shared<websocketpp::server<websocketpp::config::asio>>();
    connections = std::make_shared<con_list>();
    server->clear_access_channels(websocketpp::log::alevel::all);
    server->init_asio();
    server->set_open_handler(bind(&WebSocketServer::on_open,this,::_1));
    server->set_close_handler(bind(&WebSocketServer::on_close,this,::_1));
    server->set_message_handler([this] (connection_hdl hdl, server_t::message_ptr msg) {

        this->on_message(server, hdl, msg);
    });

}

void veezen::WebSocketServer::on_open(connection_hdl hdl) {
    std::cout << "on_open" << std::endl;
    connections->insert(std::make_pair(hdl,
                                       veezen::Client<STREAM,
                                               STREAM, TOKEN>()));
}
//            connections->insert(std::make_pair(uuid::UUID::generateRandomUUID(),hdl));


void veezen::WebSocketServer::on_close(connection_hdl hdl) {
    connections->erase(hdl);
}

void veezen::WebSocketServer::on_message( std::shared_ptr<server_t> s,
                connection_hdl hdl,
                server_t::message_ptr msg) {

    auto frame = veezen::WebsocketFrame::fromJson(msg->get_payload());

    std::cout << frame->getType() << frame->getId() << frame->getData()<< std::endl;

}
void veezen::WebSocketServer::start() {
    serverThread = std::thread([this] {
        server->listen(port);
        server->start_accept();
        server->run();
    });


}

void veezen::WebSocketServer::stop() {
    server->stop();
    serverThread.join();

}
