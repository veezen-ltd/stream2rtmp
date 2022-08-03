//
// Created by b0n3 on 8/3/22.
//

#ifndef VEEZEN2RTMP_RTMPPACKET_H
#define VEEZEN2RTMP_RTMPPACKET_H


#include <ostream>
#include <memory>


class RTMPPacket {
private:
    std::unique_ptr<unsigned  char *> data;
    long size;
public:
    RTMPPacket();
    virtual ~RTMPPacket();
    void setData(unsigned char *data, long size);
    unsigned char *getData();
    long getSize();
};


#endif //VEEZEN2RTMP_RTMPPACKET_H
