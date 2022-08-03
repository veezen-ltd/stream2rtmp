//
// Created by b0n3 on 8/1/22.
//

#include <iostream>
#include "RsocketServer.h"

void RsocketServer::start() {
     serverThread = std::thread([=] {
        // start accepting connections
         // @Todo: create
         rs->acceptConnection(
                 [](std::shared_ptr<RSocket> socket) {
                     std::cout << "Accepted connection" << std::endl;
                 }
         );
        rs->startAndPark([](const rsocket::SetupParameters &params)
                                    ->  std::shared_ptr<RSocketResponder> {
            std::cout << "server.startAndPark " << params << std::endl;
           // return std::make_unique<HelloStreamRequestResponder>(); // create connection to rtmp server
            //   return std::make_shared<HelloStreamRequestResponder>();
                return nullptr;
        });
    });
    LOG(INFO) << " Rsocket server started";
}

void RsocketServer::stop() {
    rs->unpark();
    serverThread.join();
    LOG(INFO) << " Rsocket server stopped";
}

void RsocketServer::setUp() {
    this->opts.address = folly::SocketAddress(this->host, this->port);
    this->opts.threads = this->threads;
    auto rss = RSocket::createServer(
            std::make_unique<TcpConnectionAcceptor>(
                    std::move(opts)));
    this->rs =  rss.release();
}

RsocketServer::RsocketServer(std::string const host,
                             int const  port, int const threads)
: host(host), port(port), threads(threads) {
    this->setUp();
}
