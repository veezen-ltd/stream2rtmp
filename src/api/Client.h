//
// Created by b0n3 on 8/6/22.
//

#ifndef VEEZEN2RTMP_CLIENT_H
#define VEEZEN2RTMP_CLIENT_H
#include <folly/json.h>
#include "UUID.h"
//#include <rsocket/RSocket.h>
//#include <PackedSyncPtr.h>
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
    template<class T,  typename FRAME, typename TOKEN>
    class Client {
    private:
        std::shared_ptr<uuid::UUID> id;
        std::shared_ptr<uuid::UUID> streamId;
        std::vector<std::string> rtmpUrls;
        std::vector<std::string> params;
        bool setUp = false;
        TOKEN resumeToken;
    public:
        Client()
        {
            id = uuid::UUID::generateRandomUUID();
            streamId = nullptr;
        }

        void setId(const std::shared_ptr<uuid::UUID> &id) {
            Client::id = id;
        }

        void setStreamId(const std::shared_ptr<uuid::UUID> &streamId) {
            Client::streamId = streamId;
        }

        void setRtmpUrls(const std::vector<std::string> &rtmpUrls) {
            Client::rtmpUrls = rtmpUrls;
        }

        void setParams(const std::vector<std::string> &params) {
            Client::params = params;
        }

        void setSetUp(bool setUp) {
            Client::setUp = setUp;
        }

        virtual void inCallback(TOKEN,FRAME frame)  = 0;
        virtual void outCallback(TOKEN,FRAME frame) = 0;


        const std::shared_ptr<uuid::UUID> &getId() const {
            return this->id;
        }


        const std::shared_ptr<uuid::UUID> &getStreamId() const {
            return streamId;
        }


        const std::vector<std::string> &getRtmpUrls() const {
            return rtmpUrls;
        }
        void addRtmpUrl(const std::string &rtmpUrl) {
            rtmpUrls.push_back(rtmpUrl);
        }
        void addParam(const std::string &param) {
            params.push_back(param);
        }
        void fromDynamic(folly::dynamic json) {
            this->setId(uuid::UUID::fromString(json["id"].getString()));
            this->setStreamId(uuid::UUID::fromString(json["streamId"].getString()));
            for (auto &rtmpUrl : json["rtmpUrls"])
                this->addRtmpUrl(rtmpUrl.getString());
            for (auto &param : json["params"])
                this->addParam(param.getString());
        }
        virtual std::shared_ptr<T> fromJson(const std::string &json) {
            folly::dynamic dynamic = folly::parseJson(json);
            return T::fromDynamic(dynamic);
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
