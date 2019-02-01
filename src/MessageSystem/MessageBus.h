#ifndef OPENGL_MESSAGEBUS_H
#define OPENGL_MESSAGEBUS_H

#include <functional>
#include <queue>
#include <vector>
#include <memory>
#include "Message.h"

class MessageBus
{

    private:
        std::vector<std::function<void (Message *)>> receivers;
        std::queue<Message*> messages;

        MessageBus() {}

    public:
        MessageBus(MessageBus const&) = delete;
        MessageBus& operator=(MessageBus const&) = delete;

        static std::shared_ptr<MessageBus> instance()
        {
            static std::shared_ptr<MessageBus> s {new MessageBus};
            return s;
        }

        void addReceiver(std::function<void (Message *)> messageReceiver)
        {
            receivers.push_back(messageReceiver);
        }

        void sendMessageImpl(Message * message)
        {
            messages.push(message);
        }

        static void sendMessage(Message * message) {
            MessageBus::instance()->sendMessageImpl(message);
        }

        void notify()
        {
            while(!messages.empty()) {
                for (auto & receiver : receivers) {
                    // Get reference to pointer and notify current receiver
                    receiver(messages.front());
                }

                // Delete only pointer
                messages.pop();
            }
        }

        ~MessageBus() {
            while(!messages.empty()) {
                // Get reference to pointer and delete data associated to it
                delete messages.front();

                // Delete only pointer
                messages.pop();
            }
        }

};
#endif //OPENGL_MESSAGEBUS_H