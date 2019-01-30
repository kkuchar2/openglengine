#ifndef OPENGL_MESSAGEBUS_H
#define OPENGL_MESSAGEBUS_H

#include <functional>
#include <queue>
#include <vector>
#include "Message.h"

class MessageBus
{
    private:
        std::vector<std::function<void (Message)>> receivers;
        std::queue<Message> messages;

    public:
        MessageBus() {};

        // Add receiver for message bus messages
        void addReceiver(std::function<void (Message)> messageReceiver)
        {
            receivers.push_back(messageReceiver);
        }

        // Send message through message bus (queue it)
        void sendMessage(Message message)
        {
            messages.push(message);
        }

        // Iterate through all messages in message queue and send them to all registered receivers
        void notify()
        {
            while(!messages.empty()) {
                for (auto iter = receivers.begin(); iter != receivers.end(); iter++) {
                    (*iter)(messages.front());
                }

                messages.pop();
            }
        }

        ~MessageBus() {};
};

#endif //OPENGL_MESSAGEBUS_H
