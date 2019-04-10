#pragma once

#include "BaseCamera.h"

class OrtographicCamera : public BaseCamera {

    private:
        float width = 0.0f;
        float height = 0.0f;

    public:
        OrtographicCamera(const int width, const int height);

        void updateSize(const int width, const int height);

        glm::mat4x4 getModelMatrix() override;
        glm::mat4x4 getViewMatrix() override;
        glm::mat4x4 getProjectionMatrix() override;
};