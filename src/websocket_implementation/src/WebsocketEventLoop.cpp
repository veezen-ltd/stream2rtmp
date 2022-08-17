//
// Created by b0n3 on 8/16/22.
//

#include "WebsocketEventLoop.h"

namespace veezen {
    void WebsocketEventLoop::start() {
        thread = std::thread([this] {
            while(this->run)
            {
                WebsocketEventLoop::streamContext::getInstance()
                        ->loopAndExec();
            }
        });
    }

    void WebsocketEventLoop::setUp() {
        this->run = true;
    }

    void WebsocketEventLoop::stop(){
        this->run = false;
        thread.join();
    }
} // veezen