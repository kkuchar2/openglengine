#ifndef OPENGL_BUSNODE_H
#define OPENGL_BUSNODE_H

#include <iostream>
#include <functional>
#include "MessageBus.h"

class BusNode {

    protected:
        MessageBus * messageBus;

        std::function<void(Message)> getNotifyFunc() {
            auto messageListener = [=](Message message) -> {
                this->onNotify(message);
            };
            return messageListener;
        }

        void send(Message message) {
            messageBus->sendMessage(message);
        }

        virtual void onNotify(Message message) {
            // Do something here. Your choice. You could do something like this.
            // std::cout << "Siopao! Siopao! Siopao! (Someone forgot to implement onNotify().)" << std::endl;
        }

    public:
        BusNode(MessageBus * messageBus) {
            this->messageBus = messageBus;
            this->messageBus->addReceiver(this->getNotifyFunc());
        }

        virtual void update() {};

};

#endif //OPENGL_BUSNODE_H
