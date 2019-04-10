#pragma once

#include <glm/glm.hpp>

#include <Rose/Observable.h>

class InputSystem {

    private:
        glm::vec2 oldMousePosition = glm::vec2(0.0, 0.0);
        glm::vec2 currentMousePosition = glm::vec2(0.0, 0.0);
        glm::vec2 mousePositionDelta = glm::vec2(0.0, 0.0);

        std::vector<bool> pressed;

    public:

        std::shared_ptr<Observable<glm::vec2>> mousePositionDeltaProperty;

        static InputSystem & Instance()
        {
            static InputSystem instance;
            return instance;
        }

        InputSystem() {
            mousePositionDeltaProperty = std::make_shared<Observable<glm::vec2>>(glm::vec2(0.0, 0.0));

            for (int i = 0; i < 349; i++) {
                pressed.push_back(false);
            }
        };

    public:
        InputSystem(ShaderPool const&) = delete;

        void operator=(InputSystem const&)  = delete;

        void onCursorPositionChanged(double xpos, double ypos) {
            currentMousePosition = glm::vec2(xpos, ypos);
            mousePositionDelta = currentMousePosition - oldMousePosition;
            oldMousePosition = currentMousePosition;
            mousePositionDeltaProperty->setValue(mousePositionDelta);
        }

        void onMouseButtonPressed(int button, int action, int mods) {
            // TODO: Create property
        }

        void onMouseButtonScroll(double xoffset, double yoffset) {
            // TODO: Create property
        }

        void onKeyboardKeyPressed(int key, int scancode, int action, int mods) {
            if(action == GLFW_PRESS) {
                pressed[key] = true;
            }
            else if(action == GLFW_RELEASE) {
                pressed[key] = false;
            }
        }

};