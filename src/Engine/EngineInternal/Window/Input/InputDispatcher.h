#pragma once

#include "../Window.h"
#include "InputSystem.h"


class InputDispatcher {
    private:
        static void cursor_position_callback(GLFWwindow * window, double xpos, double ypos) {
            InputSystem::Instance().onCursorPositionChanged(xpos, ypos);
        }

        static void mouse_button_callback(GLFWwindow * window, int button, int action, int mods) {
            MouseButtonInfo info {};
            info.button = button;
            info.action = action;
            info.mods = mods;
            InputSystem::Instance().onMouseButtonPressed(info);
        }

        static void scroll_callback(GLFWwindow * window, double xoffset, double yoffset) {
            InputSystem::Instance().onMouseButtonScroll(xoffset, yoffset);
        }

        static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
            InputSystem::Instance().onKeyboardKeyPressed(key, scancode, action, mods);
        }

    public:
        static void init(std::shared_ptr<Window> &window) {
            window->setCursorPositionCallback(InputDispatcher::cursor_position_callback);
            window->setScrollCallback(InputDispatcher::scroll_callback);
            window->setKeyCallback(InputDispatcher::key_callback);
            window->setMouseButtonCallback(InputDispatcher::mouse_button_callback);
        }
};