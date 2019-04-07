#pragma once

#include "Rendering/GameObject.h"
#include "Rendering/UserScene.h"

#include "Rendering/Camera/OrtographicCamera.h"
#include "Rendering/Camera/PerspectiveCamera.h"

#include "Rendering/Primitives/Primitives.h"

#include "Exceptions/EngineException.h"
#include "Window/Input/InputDispatcher.h"

#include "Scene/Scenes.h"
#include "Utils/Utils.h"

#include "Editor/Editor.h"

#include "Rendering/TextureRenderer.h"

#include "Rendering/SceneMapper.h"

class Engine {
    public:

        std::shared_ptr<Window> window;

        std::shared_ptr<TextureRenderer> renderer;
        std::shared_ptr<Editor> editor;

        std::shared_ptr<OrtographicCamera> ortographicCamera;
        std::shared_ptr<PerspectiveCamera> perspectiveCamera;

        Observer<glm::vec2> observer;

        Subscription subscription;

        Engine() {
            window = std::make_shared<Window>(1500, 1000);

            renderer = std::make_shared<TextureRenderer>(window);

            InputDispatcher::init(window);

            ortographicCamera = std::make_shared<OrtographicCamera>(window);
            perspectiveCamera = std::make_shared<PerspectiveCamera>(window, glm::vec3(0.0, 5.0, 10.0));

            renderer->addCamera(ortographicCamera);
            renderer->addCamera(perspectiveCamera);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_DEPTH_TEST);

            editor = std::make_shared<Editor>(window);

            observer = createObserver<glm::vec2>([&](glm::vec2 v) {
                renderer->updateSize(v);
                perspectiveCamera->aspectRatio = v.x / v.y;
            });

            subscription = editor->sceneWindowSizeProperty->Subscribe(observer);
        }

        void addScene(const std::shared_ptr<UserScene> & scene) {
            renderer->addScene(SceneMapper::mapToEngine(scene));
        }

        void prepareScenes() {
            renderer->prepareScenes();
        }

        void renderingLoop() {
            prepareScenes();

            while (window->shouldBeOpened()) {
                renderer->renderToTexture();
                editor->renderFrame(window, renderer->width, renderer->height, renderer->texture);
                glfwSwapBuffers(window->window);
                glfwPollEvents();
            }

            editor->terminate();

            glfwTerminate();

            subscription->Unsubscribe();
        }
};