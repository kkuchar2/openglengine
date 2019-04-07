#pragma once

#include "Rendering/GameObject.h"
#include "Rendering/UserScene.h"

#include "Rendering/Camera/OrtographicCamera.h"
#include "Rendering/Camera/PerspectiveCamera.h"

#include "Rendering/Primitives/Primitives.h"

#include "Exceptions/EngineException.h"
#include "Window/Input/InputDispatcher.h"

#include "Utils/Utils.h"

#include "Editor/Editor.h"

#include "Rendering/TextureRenderer.h"

#include "Rendering/SceneMapper.h"

class Engine {

    private:
        std::shared_ptr<Window> window;
        std::shared_ptr<TextureRenderer> renderer;
        std::shared_ptr<Editor> editor;

        Observer<glm::vec2> observer;
        Subscription subscription;
    public:
        std::shared_ptr<OrtographicCamera> ortographicCamera;
        std::shared_ptr<PerspectiveCamera> perspectiveCamera;

        Engine();

        void addScene(const std::shared_ptr<UserScene> & scene);
        void prepareScenes();
        void renderingLoop();
};