//
// Created by b0n3 on 8/3/22.
//

#ifndef VEEZEN2RTMP_RTMPOBSERVABLE_H
#define VEEZEN2RTMP_RTMPOBSERVABLE_H
#include <exception>
#include <string>
#include <utility>
#include "../RTMPPacket.h"

using namespace  std;
class RTMPObservable {
public:
    RTMPObservable();

    virtual ~RTMPObservable();

    virtual void onNext(RTMPPacket *packet) = 0;

    virtual void onError(exception_ptr e) = 0;

    virtual RTMPPacket *poll() = 0;

    virtual void onComplete() = 0;

    class RTMPException : public std::exception {
        string message;
    public:
        explicit RTMPException(std::string message) : message(std::move(message)) {}

        const char *what() const noexcept override {
            return message.c_str();
        }


    };
};

#endif //VEEZEN2RTMP_RTMPOBSERVABLE_H
