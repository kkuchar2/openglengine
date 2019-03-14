#ifndef OPENGL_ENGINE_H
#define OPENGL_ENGINE_H

#include "Rendering/GameObject.h"
#include "Rendering/RenderScene.h"

#include "Rendering/Camera/OrtographicCamera.h"
#include "Rendering/Camera/PerspectiveCamera.h"

#include "Rendering/Primitives/Primitives.h"

#include "Exceptions/EngineException.h"
#include "Window/Input/InputDispatcher.h"

#include "Scene/Scenes.h"
#include "Utils/Utils.h"

#include "Editor/Editor.h"

#include "Rendering/TextureRenderer.h"

class Engine {
    public:

        std::shared_ptr<Window> window;

        std::shared_ptr<TextureRenderer> renderer;
        std::shared_ptr<Editor> editor;

        std::shared_ptr<OrtographicCamera> oc;
        std::shared_ptr<PerspectiveCamera> pc;

        Observer<glm::vec2> * observer;

        Engine() {
            window = std::make_shared<Window>(1000, 800);

            renderer = std::make_shared<TextureRenderer>(window);

            InputDispatcher::init(window);

            oc = std::make_shared<OrtographicCamera>(window);
            pc = std::make_shared<PerspectiveCamera>(window, glm::vec3(0.0, 5.0, 10.0));

            renderer->addCamera(oc);
            renderer->addCamera(pc);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_DEPTH_TEST);

            editor = std::make_shared<Editor>(window);

            observer = new Observer<glm::vec2>([&](glm::vec2 v) {
                renderer->updateSize(v);
            });


            // TODO: Handle subscription
            //       For now subscription is created as temporary object in Subscribe
            //       We should create subscription as dynamic object
            //       After that clean that subscription in disposal of engine

            editor->sceneWindowSizeProperty->Subscribe(observer);
        }

        void addScene(std::shared_ptr<RenderScene> & scene) {
            renderer->addScene(scene);
        }

        void prepareScenes() {
            renderer->prepareScenes();
        }

        void renderingLoop() {
            prepareScenes();

            while (window->shouldBeOpened()) {
                renderer->renderToTexture();
                editor->renderFrame(window, static_cast<int>(renderer->texWidth), static_cast<int>(renderer->texHeight), renderer->renderedTexture);
                glfwGetFramebufferSize(window->window, &window->width, &window->height);
                glfwSwapBuffers(window->window);
                glfwPollEvents();
            }

            editor->terminate();

            glfwTerminate();

            delete observer;
        }
};

#endif //OPENGL_ENGINE_H
