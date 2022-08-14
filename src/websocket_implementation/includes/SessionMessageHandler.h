//
// Created by b0n3 on 8/13/22.
//

#ifndef VEEZEN2RTMP_SESSIONMESSAGEHANDLER_H
#define VEEZEN2RTMP_SESSIONMESSAGEHANDLER_H


#include "MessageService.h"

namespace veezen {

    class SessionMessageHandler : public  MessageService {
    public:
        SessionMessageHandler() = default;
        bool canHandle(const std::string &type) override;
        bool canHandle(std::shared_ptr<veezen::WebsocketFrame>frame) override;
        void handle(std::shared_ptr<veezen::WebsocketFrame> frame, connection_hdl hdl) override;
    };

} // veezen

#endif //VEEZEN2RTMP_SESSIONMESSAGEHANDLER_H
