#ifndef OPENGL_ORTHOGRAPHICPROJECTIONRENDERER_H
#define OPENGL_ORTHOGRAPHICPROJECTIONRENDERER_H

#include "BaseCamera.h"

class OrtographicCamera : public BaseCamera {
    public:
        explicit OrtographicCamera(std::shared_ptr<Window> & window) : BaseCamera(window) {
            projection = ORTOGRAPHIC;
        }

        glm::vec3 getScaleCorrection() override {
            return glm::vec3(1.0f);
        }

        glm::mat4x4 getModelMatrix() override {
            return glm::translate(glm::mat4(1.0), glm::vec3(-window->width / 2.0f, -window->height / 2.0f, 0.0f));
        }

        glm::mat4x4 getViewMatrix() override {
            return glm::mat4(1.0);
        }

        glm::mat4x4 getProjectionMatrix() override {
            return glm::ortho(-(float) window->width / 2.0f, (float) window->width / 2.0f, (float) window->height / 2.0f, -(float) window->height / 2.0f, -1000.0f, 1000.0f);
        }
};

#endif //OPENGL_ORTHOGRAPHICPROJECTIONRENDERER_H
