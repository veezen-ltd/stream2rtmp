//
// Created by b0n3 on 8/14/22.
//

#ifndef VEEZEN2RTMP_TYPES_H
#define VEEZEN2RTMP_TYPES_H
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <yarpl/flowable/Flowable.h>
#include <map>

using websocketpp::connection_hdl;

typedef std::string TOKEN;
typedef websocketpp::server<websocketpp::config::asio> server_t;
typedef std::shared_ptr<yarpl::flowable::Flowable<server_t::message_ptr>> STREAM;
typedef std::shared_ptr<veezen::Client<STREAM, STREAM, TOKEN>> veeClient;
typedef std::map<connection_hdl,veeClient,
        std::owner_less<connection_hdl>> con_list;
#endif //VEEZEN2RTMP_TYPES_H
