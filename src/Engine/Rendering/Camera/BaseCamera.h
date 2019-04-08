#pragma once

#include <iostream>
#include <memory>
#include <functional>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Mesh.h"
#include "../../Window/Window.h"
#include "../../Utils/MatrixUtils.h"
#include "../EngineObject.h"
#include "../GameObject.h"

enum Projection {
    PERSPECTIVE,
    ORTOGRAPHIC,
};

class BaseCamera : public Component {

    protected:

        std::shared_ptr<Window> window;

    public:

        Projection projection;

        explicit BaseCamera(std::shared_ptr<Window> & window) {
            this->window = window;
        }

        void render(const std::shared_ptr<EngineObject> & object, int instancesCount) {

            std::shared_ptr<Mesh> mesh = object->getMesh();

            if (!mesh) {
                return;
            }

            std::shared_ptr<Shader> shader = mesh->shader;

            shader->use();

            // Set camera position
            shader->setVec3("viewPos", getPosition());

            mesh->shaderInit(shader);

            if (mesh->textureId != 0) {
                glBindTexture(GL_TEXTURE_2D, mesh->textureId);
            }

            mesh->Render(instancesCount);
        }

        glm::mat4 createMVP(const std::shared_ptr<EngineObject> & object) {
            glm::mat4 modelMatrix = getModelMatrix();

            glm::mat4 m = glm::translate(getModelMatrix(), object->getTransform().position);
            m *= MatrixUtils::rotationMatrix(object->getTransform().rotation);
            m *= MatrixUtils::scaleMatrix(object->getTransform().scale);

            glm::mat4 mvp = getProjectionMatrix() * getViewMatrix() * m;

            return mvp;
        }

        virtual glm::vec3 getScaleCorrection() {
            return glm::vec3(1.0f);
        }

        virtual glm::vec3 getPosition() {
            return glm::vec3(0.0f, 0.0f, 0.0f);
        }

        virtual void onPointerDeltaChanged(glm::vec2 & delta) {}

        virtual void onMouseButtonPressed(int button, int action) {}

        virtual void onKeysPressedStateReceived(std::vector<bool> & pressed_keys) {}

        virtual glm::mat4x4 getModelMatrix() = 0;

        virtual glm::mat4x4 getViewMatrix() = 0;

        virtual glm::mat4x4 getProjectionMatrix() = 0;

        void onNotify(std::shared_ptr<Message> & message) override {

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
};