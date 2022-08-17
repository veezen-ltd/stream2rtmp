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
        auto client = std::make_shared<WebsocketClient>();
        if(context->getClient(hdl) != nullptr) {
            context->getServer()->close(hdl,
                                        websocketpp::close::status::policy_violation,
                                        "Already connected");
            context->deleteClient(hdl);
            return ;
        }
        context->addClient(hdl,client);
        context->getServer()->send(hdl,
                                   folly::toJson(("id",client->getId()->getId())) ,
                                   websocketpp::frame::opcode::text);
        auto streamContext = streamContext::getInstance();
        streamContext->registerInQueue(hdl);
    }

    bool SessionMessageHandler::canHandle(const std::string &type) {
        return type == "session";
    }

    bool SessionMessageHandler::canHandle(std::shared_ptr<veezen::WebsocketFrame> frame) {
        return canHandle(frame->getType());
    }
} // veezen