#pragma once

#include "Engine/EngineInternal/Rendering/Camera/BaseCamera.h"

class OrtographicCamera : public BaseCamera {

    private:
        float width = 0.0f;
        float height = 0.0f;

    public:
        OrtographicCamera(const glm::vec2 & size);

        void updateSize(const glm::vec2 & size);

        glm::mat4x4 getViewMatrix() override;
        glm::mat4x4 getProjectionMatrix() override;

        void Update() override;
};