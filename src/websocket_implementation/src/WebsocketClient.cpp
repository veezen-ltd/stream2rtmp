//
// Created by b0n3 on 8/17/22.
//

#include "WebsocketClient.h"
#include "WebsocketEventLoop.h"

using streamContext = veezen::WebsocketEventLoop::streamContext;
void WebsocketClient::inCallback(connection_hdl hdl, std::shared_ptr<veezen::WebsocketFrame> frame) {
    std::cout << "inCallback" << std::endl;
    auto streamContext = streamContext::getInstance();


        streamContext->addToOutQueue(hdl, frame);

}

void WebsocketClient::outCallback(connection_hdl hdl,std::shared_ptr<veezen::WebsocketFrame> frame) {
    std::cout << "outCallback" << std::endl;
    auto context = veezen::WebsocketContext::getInstance();
    auto server = context->getServer();
    server->send(hdl, frame->toJson(), websocketpp::frame::opcode::text);
}
