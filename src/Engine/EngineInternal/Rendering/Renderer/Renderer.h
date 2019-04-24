#pragma once

#include <glad.h>

#include "SceneDefinition/Scene.h"

#include "Camera/OrtographicCamera.h"
#include "Camera/PerspectiveCamera.h"
#include "MeshInfo.h"

#include <Primitives/Quad.h>

#include <thread>
#include <future>

class Renderer {

    private:

        std::vector<std::shared_ptr<MeshInfo>> meshes;

        std::map<std::string, std::shared_ptr<MeshInfo>> instancedMeshes;

        std::shared_ptr<BaseCamera> getCamera(const Projection & projection);

        int allInstancedCount = 0;

    public:

        double width = 1.0;
        double height = 1.0;

        GLuint texture = 0;
        GLuint dephRenderBuffer = 0;
        GLuint framebufferName = 0;

        std::shared_ptr<OrtographicCamera> ortographicCamera;
        std::shared_ptr<PerspectiveCamera> perspectiveCamera;

        std::vector<std::shared_ptr<GameObject>> gameObjects;

        explicit Renderer(const std::shared_ptr<Window> & window);

        void addScene(const std::shared_ptr<Scene> & scene);

        void prepare();

        void preprocessScenes();

        void onUpdate();

        void renderFrame();

        void createFramebuffer();

        void updateSize(const glm::vec2 & newSize);

        void logRenderMap();
};