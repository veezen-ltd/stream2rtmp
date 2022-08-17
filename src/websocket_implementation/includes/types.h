//
// Created by b0n3 on 8/14/22.
//

#ifndef VEEZEN2RTMP_TYPES_H
#define VEEZEN2RTMP_TYPES_H
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <map>
#include <futures/Future.h>
//#include "StreamContext.h"
#include "WebsocketClient.h"
using websocketpp::connection_hdl;


typedef websocketpp::server<websocketpp::config::asio> server_t;


#define  MAKE_EMPTY_CLIENT std::make_shared<WebsocketClient>>()
#endif //VEEZEN2RTMP_TYPES_H
