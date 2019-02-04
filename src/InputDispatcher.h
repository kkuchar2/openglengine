#ifndef OPENGL_INPUTDISPATCHER_H
#define OPENGL_INPUTDISPATCHER_H

#include "MessageSystem/BusNode.h"
#include "Engine/Window.h"
#include "InputSystem.h"

static InputSystem inputSystem;

class InputDispatcher {
    private:
        static void cursor_position_callback(GLFWwindow * window, double xpos, double ypos) {
            inputSystem.onCursorPositionChanged(xpos, ypos);
        }

        static void mouse_button_callback(GLFWwindow * window, int button, int action, int mods) {
            inputSystem.onMouseButtonPressed(button, action, mods);
        }

        static void scroll_callback(GLFWwindow * window, double xoffset, double yoffset) {
            inputSystem.onMouseButtonScroll(xoffset, yoffset);
        }

        static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
            inputSystem.onKeyboardKeyPressed(key, scancode, action, mods);
        }

    public:
        static void init(std::shared_ptr<Window> &window) {
            window->setCursorPositionCallback(InputDispatcher::cursor_position_callback);
            window->setScrollCallback(InputDispatcher::scroll_callback);
            window->setKeyCallback(InputDispatcher::key_callback);
            window->setMouseButtonCallback(InputDispatcher::mouse_button_callback);
        }
};


#endif //OPENGL_INPUTDISPATCHER_H
