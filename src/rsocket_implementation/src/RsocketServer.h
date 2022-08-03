//
// Created by b0n3 on 8/1/22.
//

#ifndef VEEZEN2RTMP_RSOCKETSERVER_H
#define VEEZEN2RTMP_RSOCKETSERVER_H
#include <thread>

#include <folly/init/Init.h>
#include <folly/portability/GFlags.h>
#include "folly/AtomicHashMap.h"

#include <RSocket.h>
#include <transports/tcp/TcpConnectionAcceptor.h>
using namespace rsocket;
using namespace yarpl::flowable;
using namespace folly;
#include "../../../includes/api/Server.h"

class RsocketServer : public Server{
private:
    const std::string host;
    const int port;
    const int threads;
    TcpConnectionAcceptor::Options opts;
    RSocketServer  *rs;
    std::thread serverThread;
public:
    RsocketServer(std::string const host, int  const port, int const threads);
    ~RsocketServer() override = default;
     void setUp() override;
     void start() override;
     void stop() override;
};


#endif //VEEZEN2RTMP_RSOCKETSERVER_H
