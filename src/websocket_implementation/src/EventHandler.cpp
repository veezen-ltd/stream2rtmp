//
// Created by b0n3 on 8/13/22.
//

#include "../includes/EventHandler.h"
#include "../includes/WebsocketFrame.h"

void veezen::EventHandler::on_open(connection_hdl hdl) {
    std::cout << "on_open" << std::endl;
}

void veezen::EventHandler::on_close(connection_hdl hdl) {
    std::cout << "on_close" << std::endl;
}

void veezen::EventHandler::on_message(connection_hdl hdl, server_t::message_ptr msg) {
    std::cout << "on_message" << std::endl;
    try {
        auto frame = WebsocketFrame::fromJson(msg->get_payload());
        veezen::WebsocketContext::getInstance()->getMessageService(frame)
                ->handle(frame, hdl);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}
