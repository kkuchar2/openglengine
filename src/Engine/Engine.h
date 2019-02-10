#ifndef OPENGL_ENGINE_H
#define OPENGL_ENGINE_H

#include <deps/glad/glad.h>
#include "Camera/OrtographicCamera.h"
#include "Camera/PerspectiveCamera.h"

#include "Primitives/Quad.h"
#include "Primitives/Cube.h"
#include "Primitives/Line.h"
#include "Primitives/RenderMesh.h"

#include "EngineException.h"
#include "../InputDispatcher.h"

class Engine {
    public:

        std::shared_ptr<Window> window;
        std::vector<std::shared_ptr<RenderObject>> objectsToRender;

        std::shared_ptr<OrtographicCamera> orthographicCamera;
        std::shared_ptr<PerspectiveCamera> perspectiveCamera;

        std::function<void(float)> onUpdate = [](float elapsedTime){};

        Engine() {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_SAMPLES, 4);

            window = std::make_shared<Window>(600, 600);

            InputDispatcher::init(window);

            orthographicCamera = std::make_shared<OrtographicCamera>(window);
            perspectiveCamera = std::make_shared<PerspectiveCamera>(window, glm::vec3(0.0, 5.0, 10.0));

            if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
                throw EngineException("Failed to initialize GLAD");
            }

            glEnable(GL_MULTISAMPLE);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_DEPTH_TEST);
        }

        template<typename T, typename std::enable_if<std::is_base_of<RenderObject, T>::value>::type* = nullptr>
        void addObject(std::shared_ptr<T> & obj) {
            objectsToRender.push_back(obj);
        }

        void renderObj(std::shared_ptr<RenderObject> & obj) {
            glBindTexture(GL_TEXTURE_2D, obj->textureId);
            perspectiveCamera->Render(obj);
        }

        void renderingLoop() {
            while (window->shouldBeOpened()) {

                window->UpdateTime();
                window->Update();
                perspectiveCamera->Update();
                orthographicCamera->Update();

                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                onUpdate(window->totalTime);

                for (auto & i : objectsToRender) {
                    renderObj(i);
                }

                window->swapBuffers();
                window->pollEvents();
            }
        }
};

#endif //OPENGL_ENGINE_H
