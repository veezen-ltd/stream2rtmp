//
// Created by b0n3 on 8/12/22.
//

#ifndef VEEZEN2RTMP_WEBSOCKETFRAME_H
#define VEEZEN2RTMP_WEBSOCKETFRAME_H
#include <string>
#include <folly/json.h>
#include <UUID.h>
#include <ostream>

namespace veezen {
    class WebsocketFrame {
    private:
        std::string type;
        std::shared_ptr<uuid::UUID> id;
        std::string data;
    public:
        WebsocketFrame(std::string type,
                       std::shared_ptr<uuid::UUID> id,
                       std::string data);

        static std::shared_ptr<WebsocketFrame> fromJson(std::string const  &frame);

        std::string &getType();

        std::shared_ptr<uuid::UUID> &getId();

        std::string &getData();


    };
};


#endif //VEEZEN2RTMP_WEBSOCKETFRAME_H
