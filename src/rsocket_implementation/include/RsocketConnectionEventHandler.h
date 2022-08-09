//
// Created by b0n3 on 8/9/22.
//

#ifndef VEEZEN2RTMP_RSOCKETCONNECTIONEVENTHANDLER_H
#define VEEZEN2RTMP_RSOCKETCONNECTIONEVENTHANDLER_H
#include <rsocket/RSocketConnectionEvents.h>
#include "Client.h"
#include "VeeRsocketContext.h"

namespace  veezen{
    class RsocketConnectionEventHandler : public rsocket::RSocketConnectionEvents {
    private:
        std::shared_ptr<Client> client;
    public:
        explicit RsocketConnectionEventHandler(std::shared_ptr<Client> client)
        {
            this->client = std::move(client);
        }
        void onConnected() override {
            LOG(INFO)<< client->getId() << "onConnected";
            // @Todo connect Output to rtmp packet;
            auto state = veezen::VeeRsocketContext::getInstance()
                    ->getState(client->getId()->getRef());
            client->setUpInput(state);
            client->setUpOutput(client->getInput());
        }

        void onDisconnected(const folly::exception_wrapper &wrapper) override {
            LOG(INFO) <<client->getId() <<  "  onDisconnected";
//            RSocketConnectionEvents::onDisconnected(wrapper);
        }

        void onClosed(const folly::exception_wrapper &wrapper) override {
            LOG(INFO) <<client->getId()<<  "  on closed";
//            RSocketConnectionEvents::onClosed(wrapper);
        }

        void onStreamsPaused() override {
            LOG(INFO) <<client->getId()<<  "  onStreamsPaused";
//            RSocketConnectionEvents::onStreamsPaused();
        }

        void onStreamsResumed() override {
            LOG(INFO) <<client->getId()<<  "  onStreamsResumed";
//            RSocketConnectionEvents::onStreamsResumed();
        }
    };
}
#endif //VEEZEN2RTMP_RSOCKETCONNECTIONEVENTHANDLER_H
