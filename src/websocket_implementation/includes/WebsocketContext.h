//
// Created by b0n3 on 8/13/22.
//

#ifndef VEEZEN2RTMP_WEBSOCKETCONTEXT_H
#define VEEZEN2RTMP_WEBSOCKETCONTEXT_H

//#include "types.h"
#include "MessageService.h"
#include <map>
#include <futures/Future.h>
#include "WebsocketClient.h"
typedef std::string TOKEN;
typedef folly::Future<veezen::WebsocketFrame> STREAM;
typedef std::shared_ptr<WebsocketClient> veeClient;
typedef std::map<connection_hdl,veeClient,
        std::owner_less<connection_hdl>> con_list;
using websocketpp::connection_hdl;



namespace veezen{
        class WebsocketContext {
        public:

            WebsocketContext();
            static std::shared_ptr<WebsocketContext> getInstance();
            const std::shared_ptr<con_list> &getConnections() const;
            const std::shared_ptr<server_t> &getServer() const;
            void addClient(connection_hdl &hdl, veeClient &client);
            veeClient getClient(connection_hdl hdl);
            connection_hdl getConnection(std::shared_ptr<uuid::UUID> id);
            std::shared_ptr<MessageService> getMessageService(std::shared_ptr<veezen::WebsocketFrame> frame);
            void deleteClient(connection_hdl hdl);
        private:
            static std::shared_ptr<WebsocketContext> instance;
            std::shared_ptr<con_list> connections;
            std::shared_ptr<server_t> server;
            std::vector<std::shared_ptr<MessageService>> messageServices;

   };
};

#endif //VEEZEN2RTMP_WEBSOCKETCONTEXT_H
