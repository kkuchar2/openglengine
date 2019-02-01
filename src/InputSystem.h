#ifndef OPENGL_INPUTSYSTEM_H
#define OPENGL_INPUTSYSTEM_H

#include <include/GLFW/glfw3.h>
#include "MessageSystem/BusNode.h"
#include "Engine/Window.h"
#include "MessageSystem/CursorPositionMessage.h"

class InputSystem {

    private:
        static void cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
        {
            MessageBus::sendMessage(new CursorPositionMessage(xpos, ypos));
        }

        static void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
        {
            MessageBus::sendMessage(new CursorButtonMessage(button, action, mods));
        }

        static void scroll_callback(GLFWwindow * window, double xoffset, double yoffset) {
            MessageBus::sendMessage(new ScrollMessage(xoffset, yoffset));
        }

        static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
        {
            MessageBus::sendMessage(new KeyMessage(key, scancode, action, mods));
        }

    public:
        static void init(std::shared_ptr<Window> & window) {
            window->setCursorPositionCallback(InputSystem::cursor_position_callback);
            window->setScrollCallback(InputSystem::scroll_callback);
            window->setKeyCallback(InputSystem::key_callback);
            window->setMouseButtonCallback(InputSystem::mouse_button_callback);
        }
};

#endif //OPENGL_INPUTSYSTEM_H
