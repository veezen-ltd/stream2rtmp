//
// Created by b0n3 on 8/16/22.
//

#ifndef VEEZEN2RTMP_EVENTLOOP_H
#define VEEZEN2RTMP_EVENTLOOP_H
#include "StreamContext.h"
namespace veezen {
    template<typename UNIQ_ID, typename FRAME>
    class EventLoop {
        public:
        typedef StreamContext<UNIQ_ID,
                FRAME> streamContext;
        virtual ~EventLoop() = default;
        virtual void setUp() = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
    };
};

 // veezen

#endif //VEEZEN2RTMP_EVENTLOOP_H
