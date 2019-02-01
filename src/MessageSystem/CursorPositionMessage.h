#ifndef OPENGL_CURSORPOSITIONMESSAGE_H
#define OPENGL_CURSORPOSITIONMESSAGE_H

#include "Message.h"

class CursorPositionMessage : public Message {
    public:
        double x;
        double y;

        CursorPositionMessage(double x, double y)
        : Message(MessageType::MOUSE_MOVE)
        {
            this->x = x;
            this->y = y;
        }
};

class KeyMessage : public Message {
    public:
        int key;
        int scancode;
        int action;
        int mods;

        KeyMessage(int key, int scancode, int action, int mods)
        : Message(MessageType::KEYBOARD_BUTTON)
        {
            this->key = key;
            this->scancode = scancode;
            this->action = action;
            this->mods = mods;
        }
};

class ScrollMessage : public Message {
    public:
        double xOffset;
        double yOffset;

        ScrollMessage(double xOffset, double yOffset)
        : Message(MessageType::MOUSE_SCROLL)
        {
            this->xOffset = xOffset;
            this->yOffset = yOffset;
        }
};

class CursorButtonMessage : public Message {
    public:
        int button;
        int action;
        int mods;

        CursorButtonMessage(int button, int action, int mods)
        : Message(MessageType::MOUSE_BUTTON)
        {
            this->button = button;
            this->action = action;
            this->mods = mods;
        }
};

#endif //OPENGL_CURSORPOSITIONMESSAGE_H
