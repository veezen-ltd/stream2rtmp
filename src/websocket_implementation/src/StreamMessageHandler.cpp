//
// Created by b0n3 on 8/17/22.
//

#include "StreamMessageHandler.h"

bool StreamMessageHandler::canHandle(const std::string &type) {
    return type == "stream";
}

bool StreamMessageHandler::canHandle(std::shared_ptr<veezen::WebsocketFrame> frame) {
    return canHandle(frame->getType());
}

void StreamMessageHandler::handle(std::shared_ptr<veezen::WebsocketFrame> frame,
                                  connection_hdl hdl) {
    auto streamContext = streamContext::getInstance();
    streamContext->addToInQueue(hdl , frame);
}
