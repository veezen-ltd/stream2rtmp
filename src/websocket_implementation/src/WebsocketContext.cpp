//
// Created by b0n3 on 8/13/22.
//

#include "../includes/WebsocketContext.h"

#include "../includes/SessionMessageHandler.h"
#include "StreamMessageHandler.h"
#include "types.h"
std::shared_ptr<veezen::WebsocketContext> veezen::WebsocketContext::instance = nullptr;

const std::shared_ptr<con_list> &veezen::WebsocketContext::getConnections() const {
    return connections;
}

const std::shared_ptr<server_t> &veezen::WebsocketContext::getServer() const {
    return server;
}

veezen::WebsocketContext::WebsocketContext() {
    connections = std::make_shared<con_list>();
    messageServices = std::vector<std::shared_ptr<MessageService>>();
    server = std::make_shared<websocketpp::server<websocketpp::config::asio>>();
    messageServices.push_back(std::make_shared<veezen::SessionMessageHandler>());
    messageServices.push_back(std::make_shared<StreamMessageHandler>());
}

std::shared_ptr<veezen::WebsocketContext> veezen::WebsocketContext::getInstance() {
    if(instance == nullptr)
        instance = std::make_shared<WebsocketContext>();
    return instance;
}

void veezen::WebsocketContext::addClient(connection_hdl &hdl, veeClient &client) {
    if (connections->find(hdl) != connections->end())
        throw std::runtime_error("client already exists");
    connections->insert(std::make_pair(hdl, client));
}

veeClient veezen::WebsocketContext::getClient(connection_hdl hdl) {
    if (connections->find(hdl) == connections->end())
        return nullptr;
    return connections->at(hdl);
}

std::shared_ptr<MessageService>
        veezen::WebsocketContext::getMessageService(std::shared_ptr<veezen::WebsocketFrame> frame) {
    for(auto messageService : messageServices) {
        if(messageService->canHandle(frame))
            return messageService;
    }
    throw std::runtime_error("no message service found");
}

void veezen::WebsocketContext::deleteClient(connection_hdl hdl) {
    if (connections->find(hdl) == connections->end())
        return;
    connections->erase(hdl);
}

connection_hdl WebsocketContext::getConnection(std::shared_ptr<uuid::UUID> id) {
    for(const auto& connection : *connections) {
        if(connection.second->getId() == id)
            return connection.first;
    }
    return connection_hdl();
}

