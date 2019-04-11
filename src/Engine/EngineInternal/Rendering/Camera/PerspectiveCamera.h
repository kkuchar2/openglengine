#pragma once

#include "BaseCamera.h"

class PerspectiveCamera : public BaseCamera {

    private:

        glm::vec3 lookDirectionVector = glm::vec3(0.0, 0.0, 0.0);
        glm::vec3 frontVector = glm::vec3(0.0, 0.0, -1.0);
        glm::vec3 upVector = glm::vec3(0.0, 1.0, 0.0);
        glm::vec3 velocity = glm::vec3(0.0);

    public:
        glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
        glm::vec3 lookAt = glm::vec3(0.0f, 0.0f, 0.0f);

        float fovy = 45.0f;

        float yaw = 0.0f;
        float pitch = 0.0f;
        bool rightMousePressed = false;
        bool disableMovement = false;

        float aspectRatio = 1.0;

        float currentFrame = 0.0f;
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        PerspectiveCamera(const glm::vec3 position) : BaseCamera() {
            this->position = position;
            lookDirectionVector = glm::normalize(lookAt - position);
            projection = PERSPECTIVE;
        }

        void SetPosition(const glm::vec3 & pos) {
            position = pos;
            lookDirectionVector = glm::normalize(lookAt - position);
        }

        void onMouseMove(const glm::vec2 & delta) override;
        void onMouseButtonPressed(const MouseButtonInfo & info) override;
        void onKeyInfoReceived(const KeyInfo & keyInfo) override;

        void Update() override {
            currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            position += velocity * deltaTime;
        }

        glm::vec3 getPosition() override;
        glm::mat4x4 getModelMatrix() override;
        glm::mat4x4 getViewMatrix() override;
        glm::mat4x4 getProjectionMatrix() override;
};