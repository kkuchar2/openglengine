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
        std::vector<std::function<void (std::shared_ptr<Message>&)>> receivers;
        std::queue<std::shared_ptr<Message>> messages;
        MessageBus() = default;

public:
        MessageBus(MessageBus const&) = delete;
        MessageBus& operator=(MessageBus const&) = delete;

        static std::shared_ptr<MessageBus> instance()
        {
            static std::shared_ptr<MessageBus> s {new MessageBus};
            return s;
        }

        void addReceiver(std::function<void (std::shared_ptr<Message>&)> messageReceiver)
        {
            receivers.push_back(messageReceiver);
        }

        void sendMessageImpl(std::shared_ptr<Message> & message)
        {
            messages.push(message);
            notify();
        }

        static void sendMessage(std::shared_ptr<Message> message) {
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
                messages.pop();
            }
        }

};
#endif //OPENGL_MESSAGEBUS_H