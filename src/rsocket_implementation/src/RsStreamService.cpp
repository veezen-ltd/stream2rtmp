//
// Created by b0n3 on 8/3/22.
//

#include "RsStreamService.h"

folly::Expected<RSocketConnectionParams, RSocketException>
RsStreamService::onNewSetup(const SetupParameters &parameters) {
    auto streamResponder = std::make_shared<StreamResponder>();

    return RSocketConnectionParams{
            .setup = parameters,
            .responder = streamResponder,
            .responderMetadata = std::make_shared<std::string>("Hello")
    };
}

void RsStreamService::onNewRSocketState(std::shared_ptr<RSocketServerState> ptr, ResumeIdentificationToken token) {
    RSocketServiceHandler::onNewRSocketState(ptr, token);
}

folly::Expected<std::shared_ptr<RSocketServerState>, RSocketException>
RsStreamService::onResume(ResumeIdentificationToken token) {
    return RSocketServiceHandler::onResume(token);
}

bool RsStreamService::canResume(const std::vector<StreamId> &vector, const std::vector<StreamId> &vector1,
                                ResumeIdentificationToken token) const {
    return RSocketServiceHandler::canResume(vector, vector1, token);
}
