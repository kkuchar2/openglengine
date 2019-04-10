#pragma once

#include <iostream>
#include <memory>
#include <functional>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh/Mesh.h"
#include "../../Window/Window.h"
#include "../../Utils/MatrixUtils.h"
#include "EngineObject/EngineObject.h"
#include "GameObject/GameObject.h"
#include "Projection.h"

#include <Window/Input/InputSystem.h>

class BaseCamera : public Component {

    private:

        Observer<glm::vec2> mousePositionDeltaObserver;
        Subscription mousePositionDeltaSubscription;

        // TODO: Create subscriptions and observers for keyboard and mouse buttons
        // TODO: Consider subscription cleaner to store subscriptions there and unsubscrbe at once

    public:

        Projection projection;

        BaseCamera();

        void render(const std::shared_ptr<Mesh> & mesh, int instancesCount);

        glm::mat4 createMVP(const std::shared_ptr<EngineObject> & object);

        virtual glm::vec3 getScaleCorrection();

        virtual glm::vec3 getPosition();

        virtual void onMouseMove(const glm::vec2 & delta);

        virtual void onMouseButtonPressed(int button, int action);

        virtual void onKeysPressedStateReceived(std::vector<bool> & pressed_keys);

        virtual glm::mat4x4 getModelMatrix() = 0;

        virtual glm::mat4x4 getViewMatrix() = 0;

        virtual glm::mat4x4 getProjectionMatrix() = 0;

        ~BaseCamera();
};