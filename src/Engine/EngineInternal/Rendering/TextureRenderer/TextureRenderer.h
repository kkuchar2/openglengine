#pragma once

#include <glad.h>

#include "SceneDefinition/UserScene.h"
#include "SceneDefinition/EngineScene.h"

#include "Camera/OrtographicCamera.h"
#include "Camera/PerspectiveCamera.h"

#include <Primitives/Quad.h>

class TextureRenderer {

    private:
        std::shared_ptr<Quad> quadMesh;
        int quadInstancesCount = 0;

    public:

        std::shared_ptr<BaseCamera> ortographicCamera;
        std::shared_ptr<BaseCamera> perspectiveCamera;

        double width = 400.0;
        double height = 400.0;

        GLuint texture {};
        GLuint dephRenderBuffer {};
        GLuint framebufferName = 0;

        std::map<Projection, std::vector<std::shared_ptr<EngineScene>>> scenes = {{ PERSPECTIVE, {} },{ ORTOGRAPHIC, {} }};

        TextureRenderer(const std::shared_ptr<Window> & window);

        void addScene(const std::shared_ptr<EngineScene> & scene);

        void prepare();

        void render();

        void createFrameBuffer();

        void renderToTexture();

        void updateSize(const glm::vec2 & newSize);
};