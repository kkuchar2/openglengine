#ifndef OPENGL_PERSPECTIVEPROJECTIONRENDERER_H
#define OPENGL_PERSPECTIVEPROJECTIONRENDERER_H


#include "BaseCamera.h"

std::ostream& operator<<(std::ostream & out, const glm::vec3 & v)
{
    return out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

class PerspectiveCamera : public BaseCamera {

    public:
        glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
        glm::vec3 front = glm::vec3(0.0, 0.0, -1.0);
        glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);

        glm::vec3 velocity = glm::vec3(0.0);

        float yaw = 0.0f;
        float pitch = 0.0f;
        bool rightMousePressed = false;

        explicit PerspectiveCamera(std::shared_ptr<Window> & window, const glm::vec3 position) : BaseCamera(window) {
            this->position = position;
        }

        void onPointerDeltaChanged(glm::vec2 & delta) override {
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
            f.x = static_cast<float>(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
            f.y = static_cast<float>(-sin(glm::radians(pitch)));
            f.z = static_cast<float>(-cos(glm::radians(yaw)) * cos(glm::radians(pitch)));

            front = glm::normalize(f);

            //std::cout << "Front: " << front << std::endl;
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
                speed *= 10.0f;
            }

            auto velocitySum = glm::vec3(0.0);

            velocitySum += float(pressed_keys[GLFW_KEY_W]) * front * speed;
            velocitySum -= float(pressed_keys[GLFW_KEY_S]) * front * speed;
            velocitySum += float(pressed_keys[GLFW_KEY_A]) * glm::normalize(glm::cross(up, front)) * speed;
            velocitySum -= float(pressed_keys[GLFW_KEY_D]) * glm::normalize(glm::cross(up, front)) * speed;

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

        glm::mat4x4 getModelMatrix() override {
            return glm::mat4(1.0);
        }

        glm::mat4x4 getViewMatrix() override {
            return glm::lookAt(position, position + front, up);
        }

        glm::mat4x4 getProjectionMatrix() override {
            return glm::perspective(glm::radians(45.0f), window->aspectRatio, 0.1f, 1000.0f);
        }
};

#endif //OPENGL_PERSPECTIVEPROJECTIONRENDERER_H
