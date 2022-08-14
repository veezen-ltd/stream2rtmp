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
    template<typename IN , typename OUT, typename TOKEN>
    class Client {
    private:
        std::shared_ptr<uuid::UUID> id;
        std::shared_ptr<uuid::UUID> streamId;
        std::vector<std::string> rtmpUrls;
        std::vector<std::string> params;
        bool setUp = false;
        TOKEN resumeToken;
        IN input;
        OUT output;
    public:
        Client()
        {
            id = uuid::UUID::generateRandomUUID();
            streamId = nullptr;
        }

     static  std::shared_ptr<Client<IN, OUT, TOKEN>> fromDynamic(folly::dynamic json) {
            std::shared_ptr<Client> client = std::make_shared<Client>();
            client->id =  uuid::UUID();
            client->streamId = uuid::UUID::fromString(json["streamId"].getString());
            for (auto &rtmpUrl : json["rtmpUrls"])
                client->rtmpUrls.push_back(rtmpUrl.getString());
            for (auto &param : json["params"])
                client->params.push_back(param.getString());
            return client;
        }



        void setUpInput(IN in) {
            input = in;
        }


        void setUpOutput(OUT out) {
            output = out;
        }

        const std::shared_ptr<uuid::UUID> &getId() const {
            return this->id;
        }


        const std::shared_ptr<uuid::UUID> &getStreamId() const {
            return streamId;
        }


        const std::vector<std::string> &getRtmpUrls() const {
            return rtmpUrls;
        }


        std::shared_ptr<veezen::Client<IN, OUT, TOKEN>> fromJson(const std::string &json) {
            folly::dynamic dynamic = folly::parseJson(json);
            return fromDynamic(dynamic);
        }


        const IN &getInput() const {
            return input;
        }


        const OUT &getOutput() const {
            return output;
        }


        const TOKEN &getResumeToken() const {
            return resumeToken;
        }



        void setResumeToken(const TOKEN &token) {
            this->resumeToken = token;
        }


        const std::vector<std::string> &getParams() const {
            return params;
        }
    };


}
#endif //VEEZEN2RTMP_CLIENT_H
