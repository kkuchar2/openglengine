#pragma once

#include "Engine/EngineInternal/Rendering/Camera/BaseCamera.h"

enum Plane {
    Right = 0,
    Left,
    Bottom,
    Top,
    Far,
    Near
};

class PerspectiveCamera : public BaseCamera {

    private:

        glm::vec4 planes[6];

        glm::vec3 lookDirectionVector = glm::vec3(0.0, 0.0, 0.0);
        glm::vec3 frontVector = glm::vec3(0.0, 0.0, -1.0);
        glm::vec3 upVector = glm::vec3(0.0, 1.0, 0.0);
        glm::vec3 velocity = glm::vec3(0.0);

    public:
        std::shared_ptr<Vec3Property> positionProperty;
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

        PerspectiveCamera(const glm::vec3 position);

        void onMouseMove(const glm::vec2 & delta) override;
        void onMouseButtonPressed(const MouseButtonInfo & info) override;
        void onKeyInfoReceived(const KeyInfo & keyInfo) override;

        void Update() override;

        void updateAspectRatio(const glm::vec2 & size);

        void setPosition(const glm::vec3 & pos);
        glm::vec3 getPosition() override;
        glm::mat4x4 getViewMatrix() override;
        glm::mat4x4 getProjectionMatrix() override;

        void calculateFrustumPlanes();

        bool testFrustum(const std::shared_ptr<GameObjectBase> & child);
};