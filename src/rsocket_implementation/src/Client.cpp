//
// Created by b0n3 on 8/10/22.
//
#include <Client.h>
using namespace veezen;

template<typename IN, typename OUT, typename TOKEN>
std::shared_ptr<Client<IN, OUT, TOKEN>> Client<IN,OUT,TOKEN>::fromDynamic(folly::dynamic json) {
    std::shared_ptr<Client> client = std::make_shared<Client>();
    client->id =  uuid::UUID();
    client->streamId = uuid::UUID::fromString(json["streamId"].getString());
    for (auto &rtmpUrl : json["rtmpUrls"])
        client->rtmpUrls.push_back(rtmpUrl.getString());
    for (auto &param : json["params"])
        client->params.push_back(param.getString());
    return client;
}


template<typename IN, typename OUT, typename TOKEN>
void Client<IN, OUT, TOKEN>::setUpInput(IN in) {
    input = in;
}

template<typename IN, typename OUT, typename TOKEN>
void Client<IN, OUT, TOKEN>::setUpOutput(OUT out) {
output = out;
}

template<typename IN, typename OUT, typename TOKEN>
const std::shared_ptr<uuid::UUID> &Client<IN, OUT, TOKEN>::getId() const {
    return this->id;
}

template<typename IN, typename OUT, typename TOKEN>
const std::shared_ptr<uuid::UUID> &Client<IN, OUT, TOKEN>::getStreamId() const {
    return streamId;
}

template<typename IN, typename OUT, typename TOKEN>
const std::vector<std::string> &Client<IN, OUT, TOKEN>::getRtmpUrls() const {
    return rtmpUrls;
}

template<typename IN, typename OUT, typename TOKEN>
std::shared_ptr<veezen::Client<IN, OUT, TOKEN>> Client<IN, OUT, TOKEN>::fromJson(const std::string &json) {
    folly::dynamic dynamic = folly::parseJson(json);
    return fromDynamic(dynamic);
}

template<typename IN, typename OUT, typename TOKEN>
const IN &Client<IN, OUT, TOKEN>::getInput() const {
    return input;
}

template<typename IN, typename OUT, typename TOKEN>
const OUT &Client<IN, OUT, TOKEN>::getOutput() const {
    return output;
}

template<typename IN, typename OUT, typename TOKEN>
const TOKEN &Client<IN, OUT, TOKEN>::getResumeToken() const {
    return resumeToken;
}

template<typename IN, typename OUT, typename TOKEN>
void Client<IN, OUT, TOKEN>::setResumeToken(const TOKEN &token) {
    this->resumeToken = token;
}

template<typename IN, typename OUT, typename TOKEN>
const std::vector<std::string> &Client<IN, OUT, TOKEN>::getParams() const {
    return params;
}
