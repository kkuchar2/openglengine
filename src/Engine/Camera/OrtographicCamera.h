#ifndef OPENGL_ORTHOGRAPHICPROJECTIONRENDERER_H
#define OPENGL_ORTHOGRAPHICPROJECTIONRENDERER_H

#include "BaseCamera.h"

class OrtographicCamera : public BaseCamera {
    public:
        explicit OrtographicCamera(std::shared_ptr<Window> & window) : BaseCamera(window) {}

        glm::mat4x4 getModelMatrix() override {
            return glm::scale(glm::mat4(1.0), glm::vec3(window->width - 1, window->height - 1, 1.0f));
        }

        glm::mat4x4 getViewMatrix() override {
            return glm::mat4(1.0);
        }

        glm::mat4x4 getProjectionMatrix() override {
            return glm::ortho(-(float) window->width, (float) window->width, (float) window->height, -(float) window->height, -1000.0f, 1000.0f);
        }
};

#endif //OPENGL_ORTHOGRAPHICPROJECTIONRENDERER_H
