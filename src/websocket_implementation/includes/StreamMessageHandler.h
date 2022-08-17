//
// Created by b0n3 on 8/17/22.
//

#ifndef VEEZEN2RTMP_STREAMMESSAGEHANDLER_H
#define VEEZEN2RTMP_STREAMMESSAGEHANDLER_H
#include "StreamContext.h"
#include "MessageService.h"
#include "WebsocketEventLoop.h"

using streamContext = veezen::WebsocketEventLoop::streamContext;
class StreamMessageHandler : public MessageService{
public:
    ~StreamMessageHandler() override = default;

    bool canHandle(const std::string &type) override;
    bool canHandle(std::shared_ptr<veezen::WebsocketFrame> frame) override;
    void handle(std::shared_ptr<veezen::WebsocketFrame> frame, connection_hdl hdl) override;
};


#endif //VEEZEN2RTMP_STREAMMESSAGEHANDLER_H
