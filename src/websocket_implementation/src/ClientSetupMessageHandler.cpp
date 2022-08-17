//
// Created by b0n3 on 8/15/22.
//

#include "ClientSetupMessageHandler.h"

bool ClientSetupMessageHandler::canHandle(const std::string &type) {
    return type == "setUp";
}

bool ClientSetupMessageHandler::canHandle(std::shared_ptr<veezen::WebsocketFrame> frame) {
    return canHandle(frame->getType());
}

void ClientSetupMessageHandler::handle(std::shared_ptr<veezen::WebsocketFrame> frame, connection_hdl hdl) {
    std::cout << "ClientSetupMessageHandler::handle" << std::endl;
    auto id = frame->getId();
    if (id != nullptr)
        throw std::runtime_error("ClientSetupMessageHandler::handle: id is not null");
    auto context = veezen::WebsocketContext::getInstance();
    if (context->getClient(hdl) == nullptr) {
            context->getServer()->send(hdl,
                               folly::toJson(("error","no session found")),
                               websocketpp::frame::opcode::text);
        context->getServer()->close(hdl, websocketpp::close::status::policy_violation,
                                    "must create a session before");
        context->deleteClient(hdl);
        return;
    }
    auto client = context->getClient(hdl);

}
