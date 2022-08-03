//
// Created by b0n3 on 8/2/22.
//

#include "StreamResponder.h"

std::shared_ptr<yarpl::single::Single<Payload>>
StreamResponder::handleRequestResponse(Payload request, StreamId streamId) {
    return nullptr;
}

std::shared_ptr<yarpl::flowable::Flowable<Payload>>
StreamResponder::handleRequestStream(Payload request, StreamId streamId) {
    return RSocketResponder::handleRequestStream(request, streamId);
}

std::shared_ptr<yarpl::flowable::Flowable<Payload>> StreamResponder::handleRequestChannel(Payload request,
                                                                                          std::shared_ptr<yarpl::flowable::Flowable<Payload>> requestStream,
                                                                                          StreamId streamId) {
    return RSocketResponder::handleRequestChannel(request, requestStream, streamId);
}

void StreamResponder::handleFireAndForget(rsocket::Payload request, rsocket::StreamId streamId) {
    RSocketResponder::handleFireAndForget(request, streamId);
}

