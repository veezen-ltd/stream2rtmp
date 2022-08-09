//
// Created by b0n3 on 8/9/22.
//

#ifndef VEEZEN2RTMP_RSOCKETRESPONDER_H
#define VEEZEN2RTMP_RSOCKETRESPONDER_H

#include <RSocketResponder.h>
#include <Payload.h>
#include <UUID.h>

namespace veezen {

    class RsocketResponder: public  rsocket::RSocketResponder {
        std::shared_ptr<yarpl::flowable::Flowable<rsocket::Payload>>
        handleRequestStream(rsocket::Payload request, rsocket::StreamId streamId) override;
    };
};

#endif //VEEZEN2RTMP_RSOCKETRESPONDER_H
