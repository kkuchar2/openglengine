#pragma once


#include <PhysicsEngine/PhysicsEngine.h>

#include <Scene/GameObject/GameObject.h>
#include <Scene/Scene.h>

#include "Engine/EngineInternal/Rendering/Camera/OrtographicCamera/OrtographicCamera.h"
#include "Engine/EngineInternal/Rendering/Camera/PerspectiveCamera/PerspectiveCamera.h"

#include "EngineException.h"
#include "Window/Input/InputDispatcher.h"

#include "Engine/Editor/Editor.h"

#include "Rendering/EngineRenderer/EngineRenderer.h"

class Engine {

    private:

        std::shared_ptr<Window> window;
        std::unique_ptr<Editor> editor;
        std::shared_ptr<PhysicsEngine> physicsEngine;

        Observer<glm::vec2> onWindowSizeChanged;
        Observer<bool> onBoundingBoxesEnablementChanged;
        Observer<bool> onVSyncValueChange;
        Observer<bool> onShowNormalsChange;

        SubscriptionContainer SC;

        double currentFrame = 0.0f;
        double lastFrame = 0.0f;
        double deltaTime = 0.0f;

        void prepareScenes();

    public:

        std::shared_ptr<EngineRenderer> engineRenderer;

        Engine();

        void start();

        void addScene(const std::shared_ptr<Scene> & scene);
};