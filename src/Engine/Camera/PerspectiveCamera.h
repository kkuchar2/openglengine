#ifndef OPENGL_PERSPECTIVEPROJECTIONRENDERER_H
#define OPENGL_PERSPECTIVEPROJECTIONRENDERER_H


#include "BaseCamera.h"

class PerspectiveCamera : public BaseCamera {

    public:
        glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
        glm::vec3 front = glm::vec3(0.0, 0.0, -1.0);
        glm::vec3 targetFront = glm::vec3(0.0, 0.0, 0.0);
        glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);
        glm::vec3 velocity = glm::vec3(0.0);

        float yaw = 0.0f;
        float pitch = 0.0f;
        bool rightMousePressed = false;
        bool disableMovement = false;

        explicit PerspectiveCamera(std::shared_ptr<Window> & window, const glm::vec3 position) : BaseCamera(window) {
            this->position = position;
            projection = PERSPECTIVE;
            targetFront = glm::normalize(glm::vec3(0.0f, 0.0f, 0.0f) - position);
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

            glm::vec3 df = glm::normalize(f) - front;
            front =  glm::normalize(f);

            targetFront += df;
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

            velocitySum += float(pressed_keys[GLFW_KEY_W]) * targetFront * speed;
            velocitySum -= float(pressed_keys[GLFW_KEY_S]) * targetFront * speed;
            velocitySum += float(pressed_keys[GLFW_KEY_A]) * glm::normalize(glm::cross(up, targetFront)) * speed;
            velocitySum -= float(pressed_keys[GLFW_KEY_D]) * glm::normalize(glm::cross(up, targetFront)) * speed;

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
            return glm::lookAt(position, position + targetFront, up);
        }

        glm::mat4x4 getProjectionMatrix() override {
            return glm::perspective(glm::radians(45.0f), window->aspectRatio, 0.1f, 1000.0f);
        }
};

#endif //OPENGL_PERSPECTIVEPROJECTIONRENDERER_H
