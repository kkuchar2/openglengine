#ifndef OPENGL_COMPONENT_H
#define OPENGL_COMPONENT_H

#include <iostream>
#include <functional>
#include "../../Utils/MessageSystem/MessageBus.h"

class MessageListener {
    protected:
        std::shared_ptr<MessageBus> messageBus;

        int receiverId;

        std::function<void(std::shared_ptr<Message>&)> getNotifyFunc() {
            std::function<void(std::shared_ptr<Message>&)> messageListener = [this](std::shared_ptr<Message> & message) -> void {
                this->onNotify(message);
            };
            return messageListener;
        }

        void send(std::shared_ptr<Message> & message) {
            messageBus->sendMessage(message);
        }

    public:
        explicit MessageListener() {
            this->messageBus = MessageBus::instance();
            receiverId = this->messageBus->addReceiver(this->getNotifyFunc());
        }

        ~MessageListener() {
            this->messageBus->removeReceiver(receiverId);
        }

        virtual void Update() {}
        virtual void onNotify(std::shared_ptr<Message> & message) {}

};

#endif //OPENGL_COMPONENT_H