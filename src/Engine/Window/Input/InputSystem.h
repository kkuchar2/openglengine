#ifndef OPENGL_INPUTSYSTEM_H
#define OPENGL_INPUTSYSTEM_H

#include <glm/glm.hpp>

class InputSystem {

    private:
        glm::vec2 oldMousePosition = glm::vec2(0.0, 0.0);
        glm::vec2 currentMousePosition = glm::vec2(0.0, 0.0);
        glm::vec2 mousePositionDelta = glm::vec2(0.0, 0.0);

        std::vector<bool> pressed;
    public:

        InputSystem() : pressed(349, false) {
        }

        void onCursorPositionChanged(double xpos, double ypos) {
            currentMousePosition = glm::vec2(xpos, ypos);
            mousePositionDelta = currentMousePosition - oldMousePosition;
            oldMousePosition = currentMousePosition;
            MessageBus::sendMessage(std::make_shared<CursorPositionMessage>(xpos, ypos));
            MessageBus::sendMessage(std::make_shared<CursorDeltaMessage>(mousePositionDelta));
        }

        void onMouseButtonPressed(int button, int action, int mods) {
            MessageBus::sendMessage(std::make_shared<CursorButtonMessage>(button, action, mods));
        }

        void onMouseButtonScroll(double xoffset, double yoffset) {
            MessageBus::sendMessage(std::make_shared<ScrollMessage>(xoffset, yoffset));
        }

        void onKeyboardKeyPressed(int key, int scancode, int action, int mods) {
            if(action == GLFW_PRESS) {
                pressed[key] = true;
            }
            else if(action == GLFW_RELEASE) {
                pressed[key] = false;
            }

            MessageBus::sendMessage(std::make_shared<KeyMessage>(pressed));
        }
};

#endif //OPENGL_INPUTSYSTEM_H
