#ifndef OPENGL_BUSNODE_H
#define OPENGL_BUSNODE_H


#include <iostream>
#include <functional>

#include "MessageBus.h"

class BusNode {


    protected:
        std::shared_ptr<MessageBus> messageBus;

        std::function<void(std::shared_ptr<Message>&)> getNotifyFunc() {
            std::function<void(std::shared_ptr<Message>&)> messageListener = [this](std::shared_ptr<Message> & message) -> void {
                this->onNotify(message);
            };
            return messageListener;
        }

        void send(std::shared_ptr<Message> & message) {
            messageBus->sendMessage(message);
        }

        virtual void onNotify(std::shared_ptr<Message> & message) {
            // Do something here. Your choice. You could do something like this.
            // std::cout << "Siopao! Siopao! Siopao! (Someone forgot to implement onNotify().)" << std::endl;
        }

    public:
        explicit BusNode() {
            this->messageBus = MessageBus::instance();
            this->messageBus->addReceiver(this->getNotifyFunc());
        }

        virtual void update() {};

};

#endif //OPENGL_BUSNODE_H