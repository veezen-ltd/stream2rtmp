//
// Created by b0n3 on 8/3/22.
//

#include "UUID.h"

uuid::UUID::UUID() {
    gen = std::mt19937(rd());
    dis = std::uniform_int_distribution<>(
            0, 15);
    dis2 = std::uniform_int_distribution<>(
            8, 11);

}


std::shared_ptr<uuid::UUID> uuid::UUID::generateRandomUUID() {
    std::shared_ptr<uuid::UUID> uuid = std::make_shared<uuid::UUID>();
    uuid->genrateStringId();
    return uuid;
}

folly::fbstring uuid::UUID::getId() {
    return this->_id;
}

void uuid::UUID::genrateStringId() {
    std::stringstream ss;
    int i;
    ss << std::hex;
    for (i = 0; i < 8; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 4; i++) {
        ss << dis(gen);
    }
    ss << "-4";
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    ss << dis2(gen);
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 12; i++) {
        ss << dis(gen);
    };
    this->_id = ss.str();
}

std::shared_ptr<uuid::UUID> uuid::UUID::fromString(folly::fbstring uuid) {
    auto uuidPtr = std::make_unique<uuid::UUID>();
    if (!uuidPtr->validate(uuid))
        throw uuid::UUID::UUIDException("Invalid UUID");
    uuidPtr->_id = std::move(uuid);
    return uuidPtr;
}
// 62c4b25d-d2d8-4dc4-8e48-53aa77843849
bool uuid::UUID::validate(folly::fbstring  & id) {
    if (id.length() != 36) return false;

    return boost::regex_match(id.c_str(),
                              boost::regex("^[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}$"));
}

uuid::UUID::UUID(std::unique_ptr<UUID> uuid): UUID() {
    this->_id = std::move(uuid->getId());
}

bool uuid::UUID::operator==(const uuid::UUID &rhs) const {
    return _id == rhs._id;
}

bool uuid::UUID::operator!=(const uuid::UUID &rhs) const {
    return !(rhs == *this);
}

std::ostream &uuid::operator<<(std::ostream &os, UUID uuid1) {
    os  << uuid1.getId();
    return os;
}

bool uuid::UUID::operator<(const uuid::UUID &rhs) const {
    return _id < rhs._id;
}

bool uuid::UUID::operator>(const uuid::UUID &rhs) const {
    return rhs < *this;
}

bool uuid::UUID::operator<=(const uuid::UUID &rhs) const {
    return !(rhs < *this);
}

bool uuid::UUID::operator>=(const uuid::UUID &rhs) const {
    return !(*this < rhs);
}

uuid::UUID &uuid::UUID::getRef() {
    return *this;
}

uuid::UUID::UUID(const uuid::UUID &uuid):UUID() {
    this->_id = uuid._id;
}
