//
// Created by b0n3 on 8/9/22.
//

#include "../include/RsocketResponder.h"
#include "../include/VeeRsocketContext.h"

std::shared_ptr<yarpl::flowable::Flowable<rsocket::Payload>>
veezen::RsocketResponder::handleRequestStream(rsocket::Payload request, rsocket::StreamId streamId) {
//    auto stringID = std::move(request.data->moveToFbString().toStdString());
//    auto clientId = uuid::UUID::fromString(stringID);
    return nullptr;
//   return veezen::VeeRsocketContext::getInstance()
//                ->getClient(clientId->getRef())
//                ->getOutput();
}
