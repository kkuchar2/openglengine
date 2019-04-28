#pragma once

#include "GameObject/GameObject.h"
#include "SceneDefinition/Scene.h"

#include "Rendering/Camera/OrtographicCamera.h"
#include "Rendering/Camera/PerspectiveCamera.h"

#include "EngineException.h"
#include "Window/Input/InputDispatcher.h"

#include "Utils/Utils.h"

#include "../Editor/Editor.h"

#include "Rendering/Renderer/Renderer.h"

class Engine {

    private:

        std::shared_ptr<Window> window;
        std::shared_ptr<Editor> editor;

        Observer<glm::vec2> onWindowSizeChanged;
        Observer<bool> onBoundingBoxesEnablementChanged;
        Observer<bool> onVSyncValueChange;

        Subscription windowSizeSubscription;
        Subscription boundingBoxSubscription;
        Subscription vSyncSubscription;

        std::shared_ptr<Renderer> renderer;

        void prepareScenes();
    public:

        Engine();

        void start();

        void addScene(const std::shared_ptr<Scene> & scene);
};