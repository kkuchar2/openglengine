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
#include "../Component.h"


class BaseCamera : public Component {

    protected:
        std::shared_ptr<Window> window;

    public:
        explicit BaseCamera(std::shared_ptr<Window> &window) {
            this->window = window;
        }

        void Render(std::shared_ptr<RenderObject> & renderObject) {
            std::shared_ptr<Shader> shader = renderObject->shader;

            shader->use();

            shader->setFloat("time", window->totalTime);
            shader->setVec2("resolution", window->getResolution());

            glm::mat4 m = glm::translate(getModelMatrix(), renderObject->transform.position);
            m *= rotMat(renderObject->transform.rotation);
            m *= scaleMatrix(renderObject->transform.scale);

            glm::mat4 mvp = getProjectionMatrix() * getViewMatrix() * m;

            shader->setMat4("mvp", mvp);
            shader->setMat4("m", m);
            shader->setMat4("v", getViewMatrix());
            renderObject->shaderFunc(shader);

            renderObject->Render();
        }

        glm::mat4 rotMat(glm::vec3 axis, float angle)
        {
            axis = normalize(axis);

            float s = static_cast<float>(sin(angle));
            float c = static_cast<float>(cos(angle));
            float oc = static_cast<float>(1.0 - c);

            return glm::mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                        oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                        oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                        0.0,                                0.0,                                0.0,                                1.0);
        }

        glm::mat4 rotMat(glm::vec3 rotation) {
            glm::mat4 rotMatX = rotMat(glm::vec3(1.0, 0.0, 0.0), rotation.x);
            glm::mat4 rotMatY = rotMat(glm::vec3(0.0, 1.0, 0.0), rotation.y);
            glm::mat4 rotMatZ = rotMat(glm::vec3(0.0, 0.0, 1.0), rotation.z);
            return rotMatX * rotMatY * rotMatZ;
        }

        glm::mat4 scaleMatrix(glm::vec3 scale)
        {
            return glm::mat4(scale.x, 0.0,     0.0,     0.0,
                        0.0,     scale.y, 0.0,     0.0,
                        0.0,     0.0,     scale.z, 0.0,
                        0.0,     0.0,     0.0,     1.0);
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
