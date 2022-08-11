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
        TOKEN resumeToken;
        static std::shared_ptr<Client<IN , OUT, TOKEN>> fromDynamic(folly::dynamic json);
        IN input;
        OUT output;
    public:
        void setUpInput(IN state);
        void setUpOutput(OUT output);
        const std::shared_ptr<uuid::UUID> &getId() const;
        const std::shared_ptr<uuid::UUID> &getStreamId() const;

        const std::vector<std::string> &getRtmpUrls() const;

        const TOKEN &getResumeToken() const;

        void setResumeToken(const TOKEN &token);

        const std::vector<std::string> &getParams() const;

        static std::shared_ptr<veezen::Client<IN , OUT , TOKEN> > fromJson(const std::string &json);

        const IN  &getInput() const;

        const OUT  &getOutput() const;
    };


}
#endif //VEEZEN2RTMP_CLIENT_H
