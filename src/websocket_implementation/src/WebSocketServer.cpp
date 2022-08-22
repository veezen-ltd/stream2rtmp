//
// Created by b0n3 on 8/12/22.
//

#include "../includes/WebSocketServer.h"
#include "../includes/WebsocketFrame.h"
#include "../includes/WebsocketContext.h"
#include "../includes/EventHandler.h"

void veezen::WebSocketServer::setUp() {
    auto server = veezen::WebsocketContext::getInstance()->getServer();
    server->clear_access_channels(websocketpp::log::alevel::all);
    server->init_asio();
    server->set_open_handler([this](auto && PH1) {
        veezen::EventHandler::on_open(std::forward<decltype(PH1)>(PH1)); });
    server->set_close_handler([this](auto && PH1) {
        veezen::EventHandler::on_close(std::forward<decltype(PH1)>(PH1)); });
    server->set_message_handler([this] (connection_hdl hdl, server_t::message_ptr msg) {
        veezen::EventHandler::on_message( hdl, msg);
    });
    eventLoop.setUp();
}

void veezen::WebSocketServer::start() {
    serverThread = std::thread([this] {
        auto server = veezen::WebsocketContext::getInstance()->getServer();
        server->listen(port);
        server->start_accept();
        server->run();
    });
    eventLoop.start();


}

void veezen::WebSocketServer::stop() {
    auto server = veezen::WebsocketContext::getInstance()->getServer();
    if (server == nullptr)
        return;
    if (server->is_listening()) {
        server->stop_listening();
    }
    server->stop();
    serverThread.join();
    eventLoop.stop();

}

veezen::WebSocketServer::~WebSocketServer() {
    stop();

}
