//
// Created by b0n3 on 8/17/22.
//

#ifndef VEEZEN2RTMP_WEBSOCKETCLIENT_H
#define VEEZEN2RTMP_WEBSOCKETCLIENT_H
#include "Client.h"
#include <common/connection_hdl.hpp>
#include "WebsocketFrame.h"
using websocketpp::connection_hdl;

class WebsocketClient : public veezen::Client<WebsocketClient, std::shared_ptr<veezen::WebsocketFrame>,
        connection_hdl> {
public:
    void inCallback(connection_hdl hdl,std::shared_ptr<veezen:: WebsocketFrame> frame) override;
    void outCallback(connection_hdl hdl,std::shared_ptr<veezen:: WebsocketFrame> frame) override;
    static  std::shared_ptr<WebsocketClient> fromDynamic(folly::dynamic json) {
        std::shared_ptr<WebsocketClient> client = std::make_shared<WebsocketClient>();
        client->fromDynamic(json);
        /// if we have somhing else in this class we should parse it here too
        return client;
    }
};


#endif //VEEZEN2RTMP_WEBSOCKETCLIENT_H
