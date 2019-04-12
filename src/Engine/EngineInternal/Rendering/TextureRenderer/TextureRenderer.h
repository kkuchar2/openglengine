#pragma once

#include <glad.h>

#include "SceneDefinition/UserScene.h"
#include "SceneDefinition/EngineScene.h"

#include "Camera/OrtographicCamera.h"
#include "Camera/PerspectiveCamera.h"

#include <Primitives/Quad.h>

class TextureRenderer {

    private:

        std::map<const char *, std::map<ShaderType,std::pair<std::shared_ptr<Mesh>, int>>> map;

    public:

        double width = 1.0;
        double height = 1.0;

        GLuint texture = 0;
        GLuint dephRenderBuffer = 0;
        GLuint framebufferName = 0;

        std::shared_ptr<OrtographicCamera> ortographicCamera;
        std::shared_ptr<PerspectiveCamera> perspectiveCamera;

        std::map<Projection, std::vector<std::shared_ptr<EngineScene>>> scenes = {{ PERSPECTIVE, {} },{ ORTOGRAPHIC, {} }};

        explicit TextureRenderer(const std::shared_ptr<Window> & window);

        void addScene(const std::shared_ptr<EngineScene> & scene);

        void prepare();

        void render();

        void createFrameBuffer();

        void renderToTexture();

        void updateSize(const glm::vec2 & newSize);
};