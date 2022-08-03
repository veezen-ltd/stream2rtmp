//
// Created by b0n3 on 8/3/22.
//

#ifndef VEEZEN2RTMP_RSSTREAMSERVICE_H
#define VEEZEN2RTMP_RSSTREAMSERVICE_H
#include <map>
#include <RSocket.h>
#include <RSocketServiceHandler.h>
#include "StreamResponder.h"
using namespace std;
using namespace rsocket;
using namespace yarpl::flowable;
using namespace folly;
class RsStreamService : public RSocketServiceHandler {
private:
    folly::Synchronized<
            map<ResumeIdentificationToken, std::shared_ptr<RSocketServerState>>,
            std::mutex>
            store;
public:
    Expected<RSocketConnectionParams, RSocketException> onNewSetup(const SetupParameters &parameters) override;

    void onNewRSocketState(std::shared_ptr<RSocketServerState> ptr, ResumeIdentificationToken token) override;

    folly::Expected<std::shared_ptr<RSocketServerState>, RSocketException>
    onResume(ResumeIdentificationToken token) override;

    bool canResume(const std::vector<StreamId> &vector, const std::vector<StreamId> &vector1,
                   ResumeIdentificationToken token) const override;
};


#endif //VEEZEN2RTMP_RSSTREAMSERVICE_H
