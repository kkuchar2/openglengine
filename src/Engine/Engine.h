#ifndef OPENGL_ENGINE_H
#define OPENGL_ENGINE_H

#include <deps/glad/glad.h>

#include "SceneScripts/GameObject.h"
#include "SceneScripts/Scene.h"

#include "tiny_obj_loader.h"

#include "Camera/OrtographicCamera.h"
#include "Camera/PerspectiveCamera.h"

#include "Primitives/Quad.h"
#include "Primitives/Cube.h"
#include "Primitives/Line.h"

#include "EngineException.h"
#include "InputDispatcher.h"

class Engine {
    public:

        std::shared_ptr<Window> window;
        std::shared_ptr<Scene> scene;

        std::shared_ptr<OrtographicCamera> orthographicCamera;
        std::shared_ptr<PerspectiveCamera> perspectiveCamera;

        std::function<void(float)> onUpdate = [](float elapsedTime){};

        Engine() {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            window = std::make_shared<Window>(600, 600);

            InputDispatcher::init(window);

            orthographicCamera = std::make_shared<OrtographicCamera>(window);
            perspectiveCamera = std::make_shared<PerspectiveCamera>(window, glm::vec3(0.0, 5.0, 10.0));

            if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
                throw EngineException("Failed to initialize GLAD");
            }

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_DEPTH_TEST);
        }

        template<typename T, typename std::enable_if<std::is_base_of<Mesh, T>::value>::type* = nullptr>
        void drawObjectNormals(std::shared_ptr<T> & renderObject, std::shared_ptr<Shader> & colorShader) {

            std::shared_ptr<GameObject> normalsGroup = std::make_shared<GameObject>();

            std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();

            for (int i = 0; i < renderObject->normals.size(); i += 3) {

                glm::vec3 normal = glm::vec3(renderObject->normals[i], renderObject->normals[i + 1], renderObject->normals[i + 2]);
                glm::vec3 vertex = glm::vec3(renderObject->vertices[i], renderObject->vertices[i + 1], renderObject->vertices[i + 2]);

                glm::vec3 start = renderObject->transform.scale * glm::vec3(vertex) + renderObject->transform.position;
                glm::vec3 end = start + glm::normalize(normal) / 10.0f;

                mesh->vertices.push_back(start.x);
                mesh->vertices.push_back(start.y);
                mesh->vertices.push_back(start.z);

                mesh->vertices.push_back(end.x);
                mesh->vertices.push_back(end.y);
                mesh->vertices.push_back(end.z);
            }

            for (unsigned int i = 0; i < mesh->vertices.size() / 3; i++) {
                mesh->indices.push_back(i);
            }

            mesh->disableNormals = true;
            mesh->renderFlag = RenderFlag::PERSPECTIVE;
            mesh->mode = GL_LINES;
            mesh->shader = colorShader;
            mesh->shaderInit = [](ShaderPtrRef shader) {
                shader->setVec4("color", glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
            };

            mesh->prepare();
            normalsGroup->addComponent(mesh);
            addObject(normalsGroup);
        }

        void renderingLoop() {
            while (window->shouldBeOpened()) {

                window->UpdateTime();
                window->Update();
                perspectiveCamera->Update();
                orthographicCamera->Update();

                glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                onUpdate(window->totalTime);

                scene->render(perspectiveCamera);

                window->swapBuffers();
                window->pollEvents();
            }
        }
};

#endif //OPENGL_ENGINE_H
