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

#include "GameObject/GameObject.h"
#include "Projection.h"

#include <Rendering/Renderer/MeshInfo.h>

#include <Window/Input/InputSystem.h>

class BaseCamera : public Component {

    private:

        Observer<glm::vec2> mousePositionDeltaObserver;
        Observer<MouseButtonInfo> mouseButtonObserver;
        Observer<KeyInfo> keyInfoObserver;

        Subscription mousePositionDeltaSubscription;
        Subscription mouseButtonSubscription;
        Subscription keyInfoSubscription;

    public:

        Projection projection = PERSPECTIVE;

        BaseCamera();

        void renderInstanced(const std::shared_ptr<MeshInfo> & info);

        void render(const std::shared_ptr<Mesh> & mesh);

        void initShaderCommon(const std::shared_ptr<Shader> & shader);

        virtual glm::vec3 getPosition();

        virtual void onMouseMove(const glm::vec2 & delta);

        virtual void onMouseButtonPressed(const MouseButtonInfo & info);

        virtual void onKeyInfoReceived(const KeyInfo & info);

        virtual glm::mat4x4 getViewMatrix() = 0;

        virtual glm::mat4x4 getProjectionMatrix() = 0;

        ~BaseCamera();
};