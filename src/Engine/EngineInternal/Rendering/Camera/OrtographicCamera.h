#pragma once

#include "BaseCamera.h"

class OrtographicCamera : public BaseCamera {

    private:
        float width = 0.0f;
        float height = 0.0f;

    public:
        OrtographicCamera(int width, int height);

        void updateSize(int width, int height);

        glm::mat4x4 getViewMatrix() override;
        glm::mat4x4 getProjectionMatrix() override;
};