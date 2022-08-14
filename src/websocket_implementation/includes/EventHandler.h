//
// Created by b0n3 on 8/13/22.
//

#ifndef VEEZEN2RTMP_EVENTHANDLER_H
#define VEEZEN2RTMP_EVENTHANDLER_H
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include "WebsocketContext.h"
#include "types.h"
using websocketpp::connection_hdl;

namespace veezen {
    class EventHandler {
    public:
        static void on_open(connection_hdl hdl);
        static void on_close(connection_hdl hdl);
        static void on_message(connection_hdl hdl,
                        server_t::message_ptr msg);
    };
}

#endif //VEEZEN2RTMP_EVENTHANDLER_H
