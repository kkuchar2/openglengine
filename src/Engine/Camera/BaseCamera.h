#ifndef OPENGL_BASECAMERA_H
#define OPENGL_BASECAMERA_H

#include <iostream>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <functional>

#include <GLFW/glfw3.h>

#include "../Window.h"
#include "../Primitives/RenderObject.h"
#include "../Shader.h"
#include "../../MessageSystem/BusNode.h"


class BaseCamera : BusNode {

    protected:
        std::shared_ptr<Window> window;

    public:
        explicit BaseCamera(std::shared_ptr<Window> &window) {
            this->window = window;
        }

        void Render(std::shared_ptr<RenderObject> &renderObject) {
            std::shared_ptr<Shader> shader = renderObject->shader;

            shader->use();

            shader->setFloat("time", window->totalTime);
            shader->setVec2("resolution", window->getResolution());

            shader->setVec3("translation", renderObject->transform.position);
            shader->setVec3("scale", renderObject->transform.scale);
            shader->setVec3("rotation", renderObject->transform.rotation);

            shader->setMat4("projection", getProjectionMatrix());
            shader->setMat4("view", getViewMatrix());
            shader->setMat4("model", getModelMatrix());

            renderObject->Render();
        }

        void onNotify(std::shared_ptr<Message> &message) override {

            switch (message->getMessageType()) {

                case MessageType::MOUSE_MOVE:
                    break;
                case MessageType::MOUSE_BUTTON: {
                    std::shared_ptr<CursorButtonMessage> m = std::dynamic_pointer_cast<CursorButtonMessage>(message);
                    onMouseButtonPressed(m->button, m->action);
                    break;
                }
                case MessageType::MOUSE_SCROLL:
                    break;
                case MessageType::KEYBOARD_BUTTON: {
                    std::shared_ptr<KeyMessage> m = std::dynamic_pointer_cast<KeyMessage>(message);
                    onKeysPressedStateReceived(m->pressed_keys);
                    break;
                }
                case MessageType::MOUSE_DELTA: {
                    std::shared_ptr<CursorDeltaMessage> m = std::dynamic_pointer_cast<CursorDeltaMessage>(message);
                    onPointerDeltaChanged(m->delta);
                    break;
                }
            }
        }

        virtual void onPointerDeltaChanged(glm::vec2 &delta) {

        }

        virtual void onMouseButtonPressed(int button, int action) {

        }

        virtual void onKeysPressedStateReceived(std::vector<bool> & pressed_keys) {

        }

        virtual glm::mat4x4 getModelMatrix() = 0;

        virtual glm::mat4x4 getViewMatrix() = 0;

        virtual glm::mat4x4 getProjectionMatrix() = 0;
};

#endif //OPENGL_BASECAMERA_H
