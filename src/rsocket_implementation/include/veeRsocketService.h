//
// Created by b0n3 on 8/8/22.
//

#ifndef VEEZEN2RTMP_VEERSOCKETSERVICE_H
#define VEEZEN2RTMP_VEERSOCKETSERVICE_H
#include <rsocket/RSocketServiceHandler.h>
#include <folly/Expected.h>
#include "RsocketConnectionEventHandler.h"
#include "VeeRsocketContext.h"
#include "RsocketResponder.h"

namespace veezen{
class VeeRsocketService : rsocket::RSocketServiceHandler {
private:

    folly::Expected<rsocket::RSocketConnectionParams, rsocket::RSocketException>
    onNewSetup(const rsocket::SetupParameters &parameters) override {

        LOG(INFO) << "onNewSetup" << parameters;
        auto client = veezen::Client::fromJson(parameters.payload.data->moveToFbString()
                .toStdString());
        client->setResumeToken(parameters.token);
        veezen::VeeRsocketContext::getInstance()->clientSetup(client);

        return rsocket::RSocketConnectionParams(std::shared_ptr<veezen::RsocketResponder>(),
                rsocket::RSocketStats::noop(),
                std::make_shared<veezen::RsocketConnectionEventHandler>(client));
    }

    void onNewRSocketState(std::shared_ptr<rsocket::RSocketServerState> ptr,
                           rsocket::ResumeIdentificationToken token) override {
        LOG(INFO) << "onNewRSocketState";
        veezen::VeeRsocketContext::getInstance()->setUpState(token, ptr);
    }
};
};
#endif //VEEZEN2RTMP_VEERSOCKETSERVICE_H
