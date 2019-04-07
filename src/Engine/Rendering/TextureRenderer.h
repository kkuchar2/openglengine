#pragma once

#include <glad.h>

#include "Camera/BaseCamera.h"
#include "UserScene.h"
#include "Camera/PerspectiveCamera.h"
#include "EngineScene.h"

class TextureRenderer {

    public:
        double width = 400.0;
        double height = 400.0;

        GLuint texture {};
        GLuint dephRenderBuffer {};
        GLuint framebufferName = 0;

        std::map<Projection, std::vector<std::shared_ptr<EngineScene>>> scenes = {{ PERSPECTIVE, {} },{ ORTOGRAPHIC, {} }};

        std::vector<std::shared_ptr<BaseCamera>> cameras;

        TextureRenderer(const std::shared_ptr<Window> & windowPtr);

        void addCamera(const std::shared_ptr<BaseCamera> & camera);

        void addScene(const std::shared_ptr<EngineScene> & scene);

        void prepareScenes();

        void renderScenes();

        void createFrameBuffer();

        void renderToTexture();

        void updateSize(const glm::vec2 & newSize);
};