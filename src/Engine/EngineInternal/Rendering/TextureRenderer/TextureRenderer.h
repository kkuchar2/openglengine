#pragma once

#include <glad.h>

#include "SceneDefinition/UserScene.h"
#include "SceneDefinition/EngineScene.h"

#include "Camera/OrtographicCamera.h"
#include "Camera/PerspectiveCamera.h"

#include <Primitives/Quad.h>

using ShaderToMeshesMap = std::map<ShaderType, std::pair<std::shared_ptr<Mesh>, int>>;

class TextureRenderer {

    private:
        /**
         * INSTANCED RENDERING
         *
         * Map that keeps unique [mesh-shader] pairs for instanced rendering
         *
         * a - mesh type            const char *
         * b - shader type          ShaderType
         * c - shader object ptr    std::shared_ptr<Mesh>
         * d - instance count       int
         *
         *                   a_1                        a_n
         *              ------------                ------------
         *               |        |
         *               |        |       ( ... )
         *              b_1      b_n
         *            /             \
         *         [c,d]          [c, d]
         */
        std::map<const char *, std::map<ShaderType,std::pair<std::shared_ptr<Mesh>, int>>> map;


        /**
         * CLASSIC RENDERING
         *
         * Vector for meshes, that will be rendered without instancing
         */
        std::vector<std::pair<std::shared_ptr<Mesh>, Transform>> meshesToRender;

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