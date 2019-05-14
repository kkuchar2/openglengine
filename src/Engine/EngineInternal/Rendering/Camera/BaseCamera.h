#pragma once

#include <iostream>
#include <memory>
#include <functional>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Properties/Vec3Property.h>

#include "Mesh/Mesh.h"

#include <Engine/EngineInternal/Window/Window.h>

#include <MatrixUtils.h>

#include <Scene/GameObject/GameObject.h>
#include "Engine/EngineInternal/Rendering/Projection.h"

#include <Window/Input/InputSystem.h>

class BaseCamera {

    private:

        Observer<glm::vec2> mousePositionDeltaObserver;
        Observer<MouseButtonInfo> mouseButtonObserver;
        Observer<KeyInfo> keyInfoObserver;

        SubscriptionContainer SC;

    public:

        Projection projection = PERSPECTIVE;

        BaseCamera();

        virtual glm::vec3 getPosition();

        virtual void onMouseMove(const glm::vec2 & delta);

        virtual void onMouseButtonPressed(const MouseButtonInfo & info);

        virtual void onKeyInfoReceived(const KeyInfo & info);

        virtual glm::mat4x4 getViewMatrix() = 0;

        virtual glm::mat4x4 getProjectionMatrix() = 0;

        virtual void Update() = 0;

        ~BaseCamera();
};