//
// Created by b0n3 on 8/15/22.
//

#ifndef VEEZEN2RTMP_STREAMCONTEXT_H
#define VEEZEN2RTMP_STREAMCONTEXT_H

#include <folly/ProducerConsumerQueue.h>



#include "WebsocketFrame.h"

#include "WebsocketContext.h"
using namespace veezen;
#include <folly/Function.h>
#include <map>

template<typename UNIQ_ID, typename FRAME>
class StreamContext {

public:
    std::map<UNIQ_ID,
    std::shared_ptr<folly::ProducerConsumerQueue<FRAME>>,std::owner_less<UNIQ_ID>> inStreams;
    std::map<UNIQ_ID, std::vector<FRAME>,std::owner_less<UNIQ_ID>> inPendingFrames;
    std::map<UNIQ_ID,
            std::shared_ptr<folly::ProducerConsumerQueue<FRAME>>,std::owner_less<UNIQ_ID>> outStreams;
    std::map<UNIQ_ID, std::vector<FRAME>,std::owner_less<UNIQ_ID>> outPendingFrames;

//    std::map<UNIQ_ID, folly::Function<FRAME> &> callbacks;
    static std::shared_ptr<StreamContext<UNIQ_ID, FRAME>> getInstance() {
        static std::shared_ptr<StreamContext<UNIQ_ID, FRAME>> instance;
        if (instance == nullptr) {
            std::cout<< "Creating new StreamContext" << std::endl;
            instance = std::make_shared<StreamContext<UNIQ_ID, FRAME>>();
        }
        return instance;
    }
    void unRegisterInQueue(UNIQ_ID id) {
        inStreams.erase(id);
        outStreams.erase(id);
        inPendingFrames.erase(id);
        outPendingFrames.erase(id);
    }

    void registerInQueue(UNIQ_ID &id) {
        inStreams[id] = std::make_shared<folly::ProducerConsumerQueue<FRAME>>(5);
        inPendingFrames[id] = std::vector<FRAME>();
        outStreams[id] = std::make_shared<folly::ProducerConsumerQueue<FRAME>>(5);
        outPendingFrames[id] = std::vector<FRAME>();
    }

    void loopAndExec() {
        FRAME f = nullptr;
        try {
            for (auto &stream: inStreams) {
                if (stream.second->read(f)) {
                    // stream.second->popFront();
                    auto context = WebsocketContext::getInstance();
                    context->getClient(stream.first)->inCallback(stream.first, f);
                }
                f = nullptr;
            }
            for (auto &stream: outStreams) {
                if (stream.second->read(f)) {
                    // stream.second->popFront();
                    auto context = WebsocketContext::getInstance();
                    context->getClient(stream.first)->outCallback(stream.first, f);
                }
                f = nullptr;
            }
        }catch(std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
    void addToOutQueue(UNIQ_ID id, FRAME &frame)
    {
        auto queue = outStreams[id];
        auto pendingQueue = outPendingFrames[id];

        if (queue == nullptr) {
            return;
        }

        while (!queue->isFull() && pendingQueue.size() > 0) {
            queue->write(pendingQueue.back());
            pendingQueue.pop_back();
        }
        if (!queue->isFull()) {
            queue->write(frame);
        } else {
            pendingQueue.push_back(frame);
        }
    }
    void addToInQueue(UNIQ_ID id, FRAME &frame) {
        auto queue = inStreams[id];
        auto pendingQueue = inPendingFrames[id];

        if (queue == nullptr) {
            return;
        }
        while (!queue->isFull() && pendingQueue.size() > 0) {
            queue->write(pendingQueue.back());
            pendingQueue.pop_back();
        }
        if (!queue->isFull()) {
            queue->write(frame);
        } else {
            pendingQueue.push_back(frame);
        }
    }
};


#endif //VEEZEN2RTMP_STREAMCONTEXT_H
