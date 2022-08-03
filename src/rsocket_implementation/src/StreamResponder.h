//
// Created by b0n3 on 8/2/22.
//

#ifndef VEEZEN2RTMP_STREAMRESPONDER_H
#define VEEZEN2RTMP_STREAMRESPONDER_H
#include <RSocket.h>
using namespace rsocket;
class StreamResponder : RSocketResponder{
    std::shared_ptr<yarpl::single::Single<Payload>> handleRequestResponse(Payload request, StreamId streamId) override;

    std::shared_ptr<yarpl::flowable::Flowable<Payload>>
    handleRequestStream(Payload request, StreamId streamId) override;

    std::shared_ptr<yarpl::flowable::Flowable<Payload>>
    handleRequestChannel(Payload request, std::shared_ptr<yarpl::flowable::Flowable<Payload>> requestStream,
                         StreamId streamId) override;

    void handleFireAndForget(rsocket::Payload request, rsocket::StreamId streamId) override;
};


#endif //VEEZEN2RTMP_STREAMRESPONDER_H
