//
// Created by b0n3 on 8/12/22.
//

#include "../includes/WebsocketFrame.h"


veezen::WebsocketFrame::WebsocketFrame(std::string type,
                                       std::shared_ptr<uuid::UUID> id, std::string data): type(type), id(id), data(data) {}


std::shared_ptr<veezen::WebsocketFrame> veezen::WebsocketFrame::fromJson(std::string const &frame) {
    auto json = folly::parseJson(frame);
    auto type = json["type"].asString();
    auto typestring = json["id"];
    std::shared_ptr<uuid::UUID> id = nullptr;
    if (!typestring.isNull())
        id = uuid::UUID::fromString(typestring.asString());
    auto data = json["data"].asString();
    return std::make_shared<veezen::WebsocketFrame>(type, id, data);
}

std::string &veezen::WebsocketFrame::getType() {
    return type;
}

std::shared_ptr<uuid::UUID> &veezen::WebsocketFrame::getId() {
    return id;
}

std::string &veezen::WebsocketFrame::getData() {
    return data;
}
