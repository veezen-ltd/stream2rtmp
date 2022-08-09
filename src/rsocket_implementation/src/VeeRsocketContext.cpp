//
// Created by b0n3 on 8/8/22.
//

#include "../include/VeeRsocketContext.h"
std::shared_ptr<veezen::VeeRsocketContext> veezen::VeeRsocketContext::instance
= std::make_shared<veezen::VeeRsocketContext>();




std::shared_ptr<veezen::VeeRsocketContext> veezen::VeeRsocketContext::getInstance() {
    return veezen::VeeRsocketContext::instance;
}

void veezen::VeeRsocketContext::clientSetup(std::shared_ptr<Client> client) {
        auto id = client->getId();
    clients->insert(std::make_pair( std::move(id->getRef()), client));
}

std::shared_ptr<veezen::Client> veezen::VeeRsocketContext::getClient(uuid::UUID const &id) {
    return clients->at(id);
}

std::shared_ptr<rsocket::RSocketServerState>
veezen::VeeRsocketContext::getState(const uuid::UUID &id) {
    return states->at(id);
}


veezen::VeeRsocketContext::VeeRsocketContext() {
        this->states = std::make_shared<std::map<uuid::UUID, std::shared_ptr<rsocket::RSocketServerState>>>();
        this->clients = std::make_shared<std::map<uuid::UUID, std::shared_ptr<Client>>>();
}

void veezen::VeeRsocketContext::setUpState(rsocket::ResumeIdentificationToken &token,
                                            std::shared_ptr<rsocket::RSocketServerState>& state) {
        auto client = getClientByToken(token);
        if (client != nullptr) {
            states->insert({std::move(client->getId()->getRef()),  state});
        }
}

std::shared_ptr<veezen::Client> veezen::VeeRsocketContext::getClientByToken(rsocket::ResumeIdentificationToken &token) {
    std::shared_ptr<veezen::Client> client = nullptr;
    for (auto &pair : *clients) {
        if (pair.second->getResumeToken() == token) {
            client = pair.second;
            break;
        }
    }
    if (client == nullptr)
        throw std::runtime_error("No client found");
    return client;
}


