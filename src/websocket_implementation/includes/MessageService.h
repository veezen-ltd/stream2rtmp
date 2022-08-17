//
// Created by b0n3 on 8/13/22.
//

#ifndef VEEZEN2RTMP_MESSAGESERVICE_H
#define VEEZEN2RTMP_MESSAGESERVICE_H

#include "WebsocketFrame.h"
#include <common/connection_hdl.hpp>
using websocketpp::connection_hdl;
class MessageService {
public:
    MessageService() = default;
    virtual ~MessageService() = default;
    virtual bool canHandle(const std::string &type) = 0  ;
   virtual bool canHandle(std::shared_ptr<veezen::WebsocketFrame> frame) = 0;
     virtual void handle(std::shared_ptr<veezen::WebsocketFrame> frame,connection_hdl hdl) = 0;
};


#endif //VEEZEN2RTMP_MESSAGESERVICE_H
