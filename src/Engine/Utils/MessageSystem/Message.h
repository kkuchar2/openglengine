#ifndef OPENGL_MESSAGE_H
#define OPENGL_MESSAGE_H

#include <string>
#include <glm/vec2.hpp>

enum class MessageType {
    MOUSE_MOVE,
    MOUSE_DELTA,
    MOUSE_BUTTON,
    MOUSE_SCROLL,
    KEYBOARD_BUTTON,
    SCENE_RESIZE
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

       virtual ~Message() = default;
};

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

class CursorDeltaMessage : public Message {
    public:
        glm::vec2 delta;

        CursorDeltaMessage(glm::vec2 delta): Message(MessageType::MOUSE_DELTA)
        {
            this->delta = delta;
        }
};

class KeyMessage : public Message {
    public:
        std::vector<bool> pressed_keys;

        KeyMessage(std::vector<bool> & pressed_keys) : Message(MessageType::KEYBOARD_BUTTON)
        {
            this->pressed_keys = pressed_keys;
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

class GUISceneWindowResizeMessage : public Message {
    public:
            double width;
            double height;

            GUISceneWindowResizeMessage(double width, double height)
                    : Message(MessageType::SCENE_RESIZE)
            {
                this->width = width;
                this->height = height;
            }
};



#endif //OPENGL_MESSAGE_H