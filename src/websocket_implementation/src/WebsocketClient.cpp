//
// Created by b0n3 on 8/17/22.
//

#include "WebsocketClient.h"

void WebsocketClient::inCallback(std::shared_ptr<veezen::WebsocketFrame> frame) {
    std::cout << "inCallback" << std::endl;
    auto id = frame->getId();
    auto streamContext = streamContext::getInstance();
//    auto context  = WebsocketContext::getInstance();

//    if (id != nullptr)
//    {
//        auto hdl = context->getConnection(id);
//        streamContext->addToOutQueue(hdl, frame);
//    }
}

void WebsocketClient::outCallback(std::shared_ptr<veezen::WebsocketFrame> frame) {
    std::cout << "outCallback" << std::endl;
}
