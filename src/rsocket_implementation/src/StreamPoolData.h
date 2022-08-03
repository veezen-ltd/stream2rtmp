//
// Created by b0n3 on 8/3/22.
//

#ifndef VEEZEN2RTMP_STREAMPOOLDATA_H
#define VEEZEN2RTMP_STREAMPOOLDATA_H
#include <map>
#include <RSocket.h>
#include <PackedSyncPtr.h>
using namespace folly;
using namespace std;
using namespace rsocket;

class StreamPoolData {
private:
    PackedSyncPtr<StreamPoolData> instance;
    PackedSyncPtr<
    map<ResumeIdentificationToken,
    std::shared_ptr<RSocketServerState>>> store;
public:
    StreamPoolData();
    ~StreamPoolData();
    void init();
    void addClient(ResumeIdentificationToken token,
                   std::shared_ptr<RSocketServerState> ptr);


#endif //VEEZEN2RTMP_STREAMPOOLDATA_H
