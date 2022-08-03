//
// Created by b0n3 on 8/3/22.
//

#include "RTMPPacket.h"

RTMPPacket::RTMPPacket() {
    data = nullptr;
    size = 0;
}

RTMPPacket::~RTMPPacket() = default;

void RTMPPacket::setData(unsigned char *data, long size) {
    this->data = std::make_unique<unsigned  char*>(data);
    this->size = size;
}

unsigned char *RTMPPacket::getData() {

    return *data;
}

long RTMPPacket::getSize() {
    return size;
}
