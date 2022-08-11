//
// Created by b0n3 on 8/8/22.
//

#ifndef VEEZEN2RTMP_VEERSOCKETCONTEXT_H
#define VEEZEN2RTMP_VEERSOCKETCONTEXT_H


#include <rsocket/RSocketServerState.h>
#include "Client.h"
#include "UUID.h"
#include <map>


namespace veezen {
    typedef std::shared_ptr<yarpl::flowable::Flowable<rsocket::Payload>> STREAM;
    typedef rsocket::ResumeIdentificationToken TOKEN;
    class VeeRsocketContext {
    private:
        std::shared_ptr<std::map<uuid::UUID,
            std::shared_ptr<rsocket::RSocketServerState>>> states;
        std::shared_ptr<std::map<uuid::UUID,
            std::shared_ptr<Client<STREAM, STREAM, TOKEN>>>> clients;
        static std::shared_ptr<veezen::VeeRsocketContext> instance;
    public:
        VeeRsocketContext();
        std::shared_ptr<veezen::Client<STREAM, STREAM, TOKEN>> getClient(uuid::UUID const &id);
        std::shared_ptr<rsocket::RSocketServerState> getState(uuid::UUID const &id);
        void clientSetup(std::shared_ptr<Client<STREAM, STREAM, TOKEN>> &client);
        std::shared_ptr<veezen::Client<STREAM, STREAM, TOKEN>> getClientByToken(TOKEN &token);
        void setUpState(TOKEN &token,
                        std::shared_ptr<rsocket::RSocketServerState>& state);
        static std::shared_ptr<veezen::VeeRsocketContext> getInstance();


    };
}

#endif //VEEZEN2RTMP_VEERSOCKETCONTEXT_H
