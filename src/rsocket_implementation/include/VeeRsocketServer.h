//
// Created by b0n3 on 8/6/22.
//

#ifndef VEEZEN2RTMP_VEERSOCKETSERVER_H
#define VEEZEN2RTMP_VEERSOCKETSERVER_H

#include "Server.h"

#include <thread>
#include <rsocket/transports/tcp/TcpConnectionAcceptor.h>
#include <rsocket/transports/tcp/TcpConnectionAcceptor.h>
#include <rsocket/RSocket.h>
namespace veezen {
    class VeeRsocketServer : public veezen::Server {
    private :
        std::string address;
        int port{};
        bool isRunning;
        int numThreads{};
        std::thread *thread{};
        rsocket::RSocketServer *rs = nullptr;
    public:
        VeeRsocketServer(std::string address, int port, int numThreads);
        ~VeeRsocketServer()  override;

        void setUp() override;

        void start() override;

        void stop() override;
    };

}
#endif //VEEZEN2RTMP_VEERSOCKETSERVER_H
