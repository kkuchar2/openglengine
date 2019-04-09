#pragma once

#include "GameObject/GameObject.h"
#include "SceneDefinition/UserScene.h"

#include "Rendering/Camera/OrtographicCamera.h"
#include "Rendering/Camera/PerspectiveCamera.h"

#include "EngineException.h"
#include "Window/Input/InputDispatcher.h"

#include "Utils/Utils.h"

#include "../Editor/Editor.h"

#include "TextureRenderer/TextureRenderer.h"
#include "SceneDefinition/SceneMapper.h"

class Engine {

    private:
        std::shared_ptr<Window> window;
        std::shared_ptr<Editor> editor;

        Observer<glm::vec2> observer;
        Subscription subscription;

        void renderGraphics();
        void prepareScenes();

    public:
        Engine();

        void addScene(const std::shared_ptr<UserScene> & scene);

        void start();

        std::shared_ptr<TextureRenderer> renderer;
};