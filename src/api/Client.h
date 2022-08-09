//
// Created by b0n3 on 8/6/22.
//

#ifndef VEEZEN2RTMP_CLIENT_H
#define VEEZEN2RTMP_CLIENT_H
#include <folly/json.h>
#include "UUID.h"
#include <rsocket/RSocket.h>
#include <PackedSyncPtr.h>
/*
 * This class is used to communicate with the server.
 * @Schema json:
 *  {
 *    "id": "",
 *    "streamId" : ""
 *    "rtmpUrls": [
 *    "rtmp://localhost:1935/live/stream"
 *    ]
 *    "params" : {
 *      "passphrase or shomting this meant to be dynamic".
 *     ...
 *    }
 */
namespace veezen {
    // @Todo make this a template
    class Client {
    private:
        std::shared_ptr<uuid::UUID> id;
        std::shared_ptr<uuid::UUID> streamId;
        std::vector<std::string> rtmpUrls;
        std::vector<std::string> params;
        rsocket::ResumeIdentificationToken resumeToken;
        static std::shared_ptr<Client> fromDynamic(folly::dynamic json);
        std::shared_ptr<yarpl::flowable::Flowable<rsocket::Payload>> input;
        std::shared_ptr<yarpl::flowable::Flowable<rsocket::Payload>> output;
    public:
        void setUpInput(std::shared_ptr<rsocket::RSocketServerState> state);
        void setUpOutput(std::shared_ptr<yarpl::flowable::Flowable<rsocket::Payload>> output);
        const std::shared_ptr<uuid::UUID> &getId() const;
        const std::shared_ptr<uuid::UUID> &getStreamId() const;

        const std::vector<std::string> &getRtmpUrls() const;

        const rsocket::ResumeIdentificationToken &getResumeToken() const;

        void setResumeToken(const rsocket::ResumeIdentificationToken &resumeToken);

        const std::vector<std::string> &getParams() const;

        static std::shared_ptr<veezen::Client> fromJson(const std::string &json);

        const std::shared_ptr<yarpl::flowable::Flowable<rsocket::Payload>> &getInput() const;

        const std::shared_ptr<yarpl::flowable::Flowable<rsocket::Payload>> &getOutput() const;
    };

    std::shared_ptr<veezen::Client> Client::fromJson(const std::string &json) {
        folly::dynamic jsonObject = folly::parseJson(json);

        return veezen::Client::fromDynamic(jsonObject);
    }

    std::shared_ptr<Client> Client::fromDynamic(folly::dynamic json) {
        std::shared_ptr<Client> client = std::make_shared<Client>();
        client->id = std::make_shared<uuid::UUID>();
        client->streamId = uuid::UUID::fromString(json["streamId"].getString());
        for (auto &rtmpUrl : json["rtmpUrls"])
            client->rtmpUrls.push_back(rtmpUrl.getString());
        for (auto &param : json["params"])
            client->params.push_back(param.getString());
        return client;
    }

    const std::shared_ptr<uuid::UUID> &Client::getId() const {
        return id;
    }

    const std::shared_ptr<uuid::UUID> &Client::getStreamId() const {
        return streamId;
    }

    const std::vector<std::string> &Client::getRtmpUrls() const {
        return rtmpUrls;
    }

    const std::vector<std::string> &Client::getParams() const {
        return params;
    }

    const std::shared_ptr<yarpl::flowable::Flowable<rsocket::Payload>> &Client::getInput() const {
        return input;
    }

    const std::shared_ptr<yarpl::flowable::Flowable<rsocket::Payload>> &Client::getOutput() const {
        return output;
    }

    void Client::setUpInput(std::shared_ptr<rsocket::RSocketServerState> state) {
     if (state != nullptr)
     {
         auto in = state->getRequester()->requestStream(rsocket::Payload(
                 folly::toJson(folly::dynamic::object("id", id->getId())),
                 folly::toJson(folly::dynamic::object("content-type",
                                                      "application/json"))));
         if(input == nullptr)
            input = in;
         else
             input.reset(in.get());
     }
    }

    void Client::setUpOutput(std::shared_ptr<yarpl::flowable::Flowable<rsocket::Payload>> out) {
            this->output = out;
    }

    const rsocket::ResumeIdentificationToken &Client::getResumeToken() const {
        return resumeToken;
    }

    void Client::setResumeToken(const rsocket::ResumeIdentificationToken &resumeToken) {
        Client::resumeToken = resumeToken;
    }

}
#endif //VEEZEN2RTMP_CLIENT_H
