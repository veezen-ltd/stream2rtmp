//
// Created by b0n3 on 8/13/22.
//

#ifndef VEEZEN2RTMP_WEBSOCKETCONTEXT_H
#define VEEZEN2RTMP_WEBSOCKETCONTEXT_H
#include <memory>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <Client.h>
#include <yarpl/flowable/Flowable.h>
#include "MessageService.h"
#include <boost/any.hpp>
#include "types.h"


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
            std::shared_ptr<MessageService> getMessageService(std::shared_ptr<veezen::WebsocketFrame> frame);

        private:
            static std::shared_ptr<WebsocketContext> instance;
            std::shared_ptr<con_list> connections;
            std::shared_ptr<server_t> server;
            std::vector<std::shared_ptr<MessageService>> messageServices;

   };
};

#endif //VEEZEN2RTMP_WEBSOCKETCONTEXT_H
