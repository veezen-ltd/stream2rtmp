//
// Created by b0n3 on 8/15/22.
//

#ifndef VEEZEN2RTMP_CLIENTSETUPMESSAGEHANDLER_H
#define VEEZEN2RTMP_CLIENTSETUPMESSAGEHANDLER_H
#include "MessageService.h"
#include "WebsocketContext.h"
#include "WebsocketEventLoop.h"
using streamContext = veezen::WebsocketEventLoop::streamContext;

class ClientSetupMessageHandler : public MessageService{
public:
    ClientSetupMessageHandler() = default;
    bool canHandle(const std::string &type) override;
    bool canHandle(std::shared_ptr<veezen::WebsocketFrame>frame) override;
    void handle(std::shared_ptr<veezen::WebsocketFrame> frame, connection_hdl hdl) override;
};

#endif //VEEZEN2RTMP_CLIENTSETUPMESSAGEHANDLER_H
