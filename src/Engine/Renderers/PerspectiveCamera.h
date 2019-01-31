#ifndef OPENGL_PERSPECTIVEPROJECTIONRENDERER_H
#define OPENGL_PERSPECTIVEPROJECTIONRENDERER_H

#include "BaseCamera.h"

class PerspectiveCamera : public BaseCamera {

    public:
        glm::vec3 position = glm::vec3(0.0);

        explicit PerspectiveCamera(Window * window, const glm::vec3 position) : BaseCamera(window) {
            this->position = position;
        }

        glm::mat4x4 getModelMatrix() override {
            return glm::mat4(1.0);
        }

        glm::mat4x4 getViewMatrix() override {
            return glm::lookAt(position, glm::vec3(0,0,0), glm::vec3(0,1,0));
        }

        glm::mat4x4 getProjectionMatrix() override {
            return glm::perspective(glm::radians(45.0f), window->aspectRatio, 0.1f, 1000.0f);
        }
};

#endif //OPENGL_PERSPECTIVEPROJECTIONRENDERER_H
