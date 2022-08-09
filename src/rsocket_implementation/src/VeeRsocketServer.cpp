//
// Created by b0n3 on 8/6/22.
//


#include "../include/VeeRsocketServer.h"

veezen::VeeRsocketServer::VeeRsocketServer(std::string address, int port, int numThreads)
: address(std::move(address)), port(port), numThreads(numThreads), isRunning(false) {
    veezen::VeeRsocketServer::setUp();

}

void veezen::VeeRsocketServer::setUp() {

    rsocket::TcpConnectionAcceptor::Options opts;
    opts.address = folly::SocketAddress(this->address, this->port);
    opts.threads = numThreads;
    auto rst = rsocket::RSocket::createServer(
            std::make_unique<rsocket::TcpConnectionAcceptor>(std::move(opts)));
    rs =  rst.release();
}

void veezen::VeeRsocketServer::start() {
    if (rs == nullptr) {
        throw std::runtime_error("Server is not initialized");
    }
    thread = new std::thread([this]() {

        // @Todo plug rsocketService here and start listening
        //this->rs->startAndPark();
    });
    this->isRunning = true;
}

void veezen::VeeRsocketServer::stop() {
    if(!this->isRunning) {
        throw std::runtime_error("Server is not running");
    }

        rs->unpark();
        thread->join();
        delete thread;
        thread = nullptr;
        this->isRunning = false;

}

veezen::VeeRsocketServer::~VeeRsocketServer() {
    if (thread != nullptr) {
        thread->join();
        delete thread;
    }
    if (rs != nullptr) {
        delete rs;
    }
}

