//
// Created by b0n3 on 8/1/22.
//

#ifndef VEEZEN2RTMP_SERVER_H
#define VEEZEN2RTMP_SERVER_H
class Server{
public:
    virtual ~Server() = default;
    virtual void setUp() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
};
#endif //VEEZEN2RTMP_SERVER_H
