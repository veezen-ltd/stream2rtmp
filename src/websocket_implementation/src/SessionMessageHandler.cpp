//
// Created by b0n3 on 8/13/22.
//

#include "../includes/SessionMessageHandler.h"
#include "../includes/WebsocketContext.h"

#include <iostream>
namespace veezen {
    void SessionMessageHandler::handle(std::shared_ptr<veezen::WebsocketFrame> frame, connection_hdl hdl) {
        std::cout << "SessionMessageHandler::handle" << std::endl;
        auto id = frame->getId();
        if (id != nullptr)
            throw std::runtime_error("SessionMessageHandler::handle: id is not null");
        auto context = veezen::WebsocketContext::getInstance();
        auto client =  veeClient();
        context->addClient(hdl,client);
        context->getServer()->send(hdl,
                                   client->getId()->getId().toStdString() ,
                                   websocketpp::frame::opcode::text);
    }

    bool SessionMessageHandler::canHandle(const std::string &type) {
        return type == "session";
    }

    bool SessionMessageHandler::canHandle(std::shared_ptr<veezen::WebsocketFrame> frame) {
        return canHandle(frame->getType());
    }
} // veezen