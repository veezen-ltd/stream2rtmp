//
// Created by b0n3 on 8/16/22.
//

#ifndef VEEZEN2RTMP_WEBSOCKETEVENTLOOP_H
#define VEEZEN2RTMP_WEBSOCKETEVENTLOOP_H
#include "EventLoop.h"
#include "WebsocketFrame.h"
namespace veezen {

class WebsocketEventLoop : public
        veezen::EventLoop<connection_hdl,
                std::shared_ptr<WebsocketFrame>> {
private:
    std::thread thread;
    bool run;
public:
    WebsocketEventLoop() = default;
    ~WebsocketEventLoop() override = default;
    void setUp() override;
    void start() override;
    void stop() override;
};


} // veezen

#endif //VEEZEN2RTMP_WEBSOCKETEVENTLOOP_H
