#pragma once

#include <glm/glm.hpp>

#include <Rose/Observable.h>
#include "MouseButtonInfo.h"
#include "KeyInfo.h"

class InputSystem {

    private:
        glm::vec2 oldMousePosition = glm::vec2(0.0, 0.0);
        glm::vec2 currentMousePosition = glm::vec2(0.0, 0.0);
        glm::vec2 mousePositionDelta = glm::vec2(0.0, 0.0);

        KeyInfo keyInfo;

    public:

        std::shared_ptr<Observable<glm::vec2>> mousePositionDeltaProperty;
        std::shared_ptr<Observable<MouseButtonInfo>> mouseButtonProperty;
        std::shared_ptr<Observable<KeyInfo>> keyInfoProperty;

        static InputSystem & Instance()
        {
            static InputSystem instance;
            return instance;
        }

        InputSystem() {
            mousePositionDeltaProperty = std::make_shared<Observable<glm::vec2>>(glm::vec2(0.0, 0.0));
            mouseButtonProperty = std::make_shared<Observable<MouseButtonInfo>>(MouseButtonInfo());
            keyInfoProperty = std::make_shared<Observable<KeyInfo>>(KeyInfo());
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

        void onMouseButtonPressed(MouseButtonInfo info) {
            mouseButtonProperty->setValue(info);
        }

        void onMouseButtonScroll(double xoffset, double yoffset) {
            // TODO: Create property
        }

        void onKeyboardKeyPressed(int key, int scancode, int action, int mods) {
            if(action == GLFW_PRESS) {
                keyInfo.pressedKeys[key] = true;
            }
            else if(action == GLFW_RELEASE) {
                keyInfo.pressedKeys[key] = false;
            }

            keyInfoProperty->setValue(keyInfo);
        }

};