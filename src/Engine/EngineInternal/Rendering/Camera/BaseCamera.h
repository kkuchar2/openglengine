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

#include <Rendering/Renderer/InstancedMeshInfo.h>

#include <Window/Input/InputSystem.h>

class BaseCamera : public Component {

    private:

        Observer<glm::vec2> mousePositionDeltaObserver;
        Observer<MouseButtonInfo> mouseButtonObserver;
        Observer<KeyInfo> keyInfoObserver;

        Subscription mousePositionDeltaSubscription;
        Subscription mouseButtonSubscription;
        Subscription keyInfoSubscription;


        glm::mat4x4 projectionMatrix = glm::mat4x4();
        glm::mat4x4 viewMatrix = glm::mat4x4();
        glm::mat4x4 projectionViewMatrix = glm::mat4x4();

    public:

        Projection projection = PERSPECTIVE;

        BaseCamera();

        void renderInstanced(const std::shared_ptr<InstancedMeshInfo> & info);

        void render(const std::shared_ptr<Mesh> & mesh, const Transform & transform);

        void initShaderCommon(const std::shared_ptr<Shader> & shader);

        static glm::mat4 createModelMatrix(const Transform & transform);

        virtual glm::vec3 getPosition();

        virtual void onMouseMove(const glm::vec2 & delta);

        virtual void onMouseButtonPressed(const MouseButtonInfo & info);

        virtual void onKeyInfoReceived(const KeyInfo & info);

        virtual glm::mat4x4 getViewMatrix() = 0;

        virtual glm::mat4x4 getProjectionMatrix() = 0;

        ~BaseCamera();
};