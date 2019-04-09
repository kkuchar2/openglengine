#pragma once

#include <iostream>
#include <functional>
#include "../../Utils/MessageSystem/MessageBus.h"

class Component {
    protected:
        std::shared_ptr<MessageBus> messageBus;

        int receiverId;

        std::function<void(std::shared_ptr<Message>&)> getNotifyFunc() {
            std::function<void(std::shared_ptr<Message>&)> Component = [this](std::shared_ptr<Message> & message) -> void {
                this->onNotify(message);
            };
            return Component;
        }

        void send(std::shared_ptr<Message> & message) {
            messageBus->sendMessage(message);
        }

    public:
        explicit Component() {
            this->messageBus = MessageBus::instance();
            receiverId = this->messageBus->addReceiver(this->getNotifyFunc());
        }

        ~Component() {
            this->messageBus->removeReceiver(receiverId);
        }

        virtual void Update() {}
        virtual void onNotify(std::shared_ptr<Message> & message) {}

};