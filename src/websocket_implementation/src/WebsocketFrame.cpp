//
// Created by b0n3 on 8/12/22.
//

#include <utility>

#include "../includes/WebsocketFrame.h"


veezen::WebsocketFrame::WebsocketFrame(std::string type,
                                       std::shared_ptr<uuid::UUID> id,
                                       folly::dynamic data):
                                       type(std::move(type)),
                                       id(std::move(id)),
                                       data(std::move(data)) {}


std::shared_ptr<veezen::WebsocketFrame> veezen::WebsocketFrame::fromJson(std::string const &frame) {
    auto json = folly::parseJson(frame);
    auto type = json["type"].asString();
    auto typestring = json["id"];
    std::shared_ptr<uuid::UUID> id = nullptr;
    if (!typestring.isNull())
        id = uuid::UUID::fromString(typestring.asString());
    auto data = std::move(json["data"]);
    return std::make_shared<veezen::WebsocketFrame>(type, id, data);
}

const std::string &veezen::WebsocketFrame::getType() const {
    return type;
}

const std::shared_ptr<uuid::UUID> &veezen::WebsocketFrame::getId()  const{
    return id;
}

const folly::dynamic &veezen::WebsocketFrame::getData() const {
    return data;
}

const std::string veezen::WebsocketFrame::toJson() const {
    folly::dynamic json = folly::dynamic::object;
    json["type"] = type;
    if (id != nullptr)
        json["id"] = id->getId();
    json["data"] = data;
    return folly::toJson(json);
}

void veezen::WebsocketFrame::setType(const std::string &type) {
    WebsocketFrame::type = type;
}

void veezen::WebsocketFrame::setId(const std::shared_ptr<uuid::UUID> &id) {
    WebsocketFrame::id = id;
}

void veezen::WebsocketFrame::setData(const folly::dynamic &data) {
    WebsocketFrame::data = data;
}
