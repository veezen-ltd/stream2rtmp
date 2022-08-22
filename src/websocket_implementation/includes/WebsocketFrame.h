//
// Created by b0n3 on 8/12/22.
//

#ifndef VEEZEN2RTMP_WEBSOCKETFRAME_H
#define VEEZEN2RTMP_WEBSOCKETFRAME_H
#include <string>
#include <folly/json.h>
#include <UUID.h>
#include <iostream>
#include <ostream>

namespace veezen {
    class WebsocketFrame {
    private:
        std::string type;
        std::shared_ptr<uuid::UUID> id;
        folly::dynamic data;

    public:
        WebsocketFrame(std::string type,
                       std::shared_ptr<uuid::UUID> id,
                       folly::dynamic data);

        static std::shared_ptr<WebsocketFrame> fromJson(std::string const  &frame);

        void setType(const std::string &type);

        void setId(const std::shared_ptr<uuid::UUID> &id);

        void setData(const folly::dynamic &data);

        const std::string &getType() const;

        const std::shared_ptr<uuid::UUID> &getId()const;

        const folly::dynamic &getData()const;
        const std::string toJson() const;


    };
};


#endif //VEEZEN2RTMP_WEBSOCKETFRAME_H
