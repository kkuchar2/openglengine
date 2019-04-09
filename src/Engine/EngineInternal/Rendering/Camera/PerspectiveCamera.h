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

        PerspectiveCamera(const std::shared_ptr<Window> & window, const glm::vec3 position) : BaseCamera(window) {
            this->position = position;
            lookDirectionVector = glm::normalize(lookAt - position);
            projection = PERSPECTIVE;
        }

        void SetPosition(const glm::vec3 & pos) {
            position = pos;
            lookDirectionVector = glm::normalize(lookAt - position);
        }

        void onPointerDeltaChanged(glm::vec2 & delta) override {

            if (disableMovement) {
                return;
            }

            if( !rightMousePressed) {
                return;
            }

            float sensitivity = 0.05;

            yaw += (delta.x  * sensitivity);
            pitch += (delta.y * sensitivity);

            if(pitch > 89.0f) {
                pitch = 89.0f;
            }

            if(pitch < -89.0f) {
                pitch = -89.0f;
            }

            glm::vec3 f;
            f.x = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            f.y = -sin(glm::radians(pitch));
            f.z = -cos(glm::radians(yaw)) * cos(glm::radians(pitch));

            glm::vec3 df = glm::normalize(f) - frontVector;
            frontVector =  glm::normalize(f);

            lookDirectionVector += df;
        }

        void onMouseButtonPressed(int button, int action) override {
            if (button == GLFW_MOUSE_BUTTON_RIGHT) {
                if (action == GLFW_PRESS && !rightMousePressed) {
                    rightMousePressed = true;
                }
                else if (rightMousePressed) {
                    rightMousePressed = false;
                }
            }
        }

        void onKeysPressedStateReceived(std::vector<bool> & pressed_keys) override {
            float speed = 0.5f;

            if (pressed_keys[GLFW_KEY_LEFT_CONTROL]) {
                speed *= 0.1f;
            }

            if (pressed_keys[GLFW_KEY_LEFT_SHIFT]) {
                speed *= 20.0f;
            }

            auto velocitySum = glm::vec3(0.0);

            velocitySum += float(pressed_keys[GLFW_KEY_W]) * lookDirectionVector * speed;
            velocitySum -= float(pressed_keys[GLFW_KEY_S]) * lookDirectionVector * speed;
            velocitySum += float(pressed_keys[GLFW_KEY_A]) * glm::normalize(glm::cross(upVector, lookDirectionVector)) * speed;
            velocitySum -= float(pressed_keys[GLFW_KEY_D]) * glm::normalize(glm::cross(upVector, lookDirectionVector)) * speed;

            velocity = velocitySum;
        }

        float currentFrame = 0.0f;
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        void Update() override {
            currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            position += velocity * deltaTime;
        }

        glm::vec3 getPosition() override {
            return position;
        }

        glm::mat4x4 getModelMatrix() override {
            return glm::mat4(1.0);
        }

        glm::mat4x4 getViewMatrix() override {
            return glm::lookAt(position, position + lookDirectionVector, upVector);
        }

        glm::mat4x4 getProjectionMatrix() override {
            return glm::perspective(glm::radians(fovy), aspectRatio, 0.1f, 1000.0f);
        }
};