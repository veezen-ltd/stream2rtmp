//
// Created by b0n3 on 8/17/22.
//

#ifndef VEEZEN2RTMP_WEBSOCKETCLIENT_H
#define VEEZEN2RTMP_WEBSOCKETCLIENT_H
#include "Client.h"

#include "WebsocketFrame.h"
#include "WebsocketEventLoop.h"

using streamContext = veezen::WebsocketEventLoop::streamContext;

class WebsocketClient : public veezen::Client<WebsocketClient, std::shared_ptr<veezen::WebsocketFrame>,
        std::string> {
public:
    void inCallback(std::shared_ptr<veezen:: WebsocketFrame> frame) override;
    void outCallback(std::shared_ptr<veezen:: WebsocketFrame> frame) override;
    static  std::shared_ptr<WebsocketClient> fromDynamic(folly::dynamic json) {
        std::shared_ptr<WebsocketClient> client = std::make_shared<WebsocketClient>();
        client->fromDynamic(json);
        /// if we have somhing else in this class we should parse it here too
        return client;
    }
};


#endif //VEEZEN2RTMP_WEBSOCKETCLIENT_H
