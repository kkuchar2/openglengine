#ifndef OPENGL_MSG_H
#define OPENGL_MSG_H

#include <string>

class Message
{
    private:
        std::string messageEvent;

    public:
        Message(const std::string event)
        {
            messageEvent = event;
        }

        std::string getEvent()
        {
            return messageEvent;
        }
};

#endif //OPENGL_MSG_H
