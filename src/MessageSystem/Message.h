#ifndef OPENGL_MESSAGE_H
#define OPENGL_MESSAGE_H

#include <string>

enum MessageType {
    MOUSE_MOVE,
    MOUSE_BUTTON,
    MOUSE_SCROLL,
    KEYBOARD_BUTTON,
};

class Message
{
    private:
        MessageType messageType;

    public:
        explicit Message(const MessageType messageType)
        {
            this->messageType = messageType;
        }

        MessageType getMessageType()
        {
            return messageType;
        }
};

#endif //OPENGL_MESSAGE_H