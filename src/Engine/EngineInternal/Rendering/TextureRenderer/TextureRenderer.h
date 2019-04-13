#pragma once

#include <glad.h>

#include "SceneDefinition/UserScene.h"
#include "SceneDefinition/EngineScene.h"

#include "Camera/OrtographicCamera.h"
#include "Camera/PerspectiveCamera.h"

#include <Primitives/Quad.h>

using ShaderToMeshesMap = std::map<ShaderType, std::pair<std::shared_ptr<Mesh>, int>>;

/**
 * If we want to render mesh:
 *
 * 1. Create mesh prototype
 * 2. Set prototype mesh type (or mesh path)
 * 3. Set prototype instancing mode to true or false
 * 4. Set prototype mesh shader (if we use instancing, we need to specify instaced shader)
 * 5. Set optional texture
 * 6. Set optional color
 *
 * NOTE: For now instanced rendering groups unique meshes based
 * on mesh type (or mesh path) and shader type. If we use the same
 * shader type and the same mesh type, meshes will not be rendered (just one).
 *
 * TODO: Consider grouping through something as 'material'
 *
 * We have to fix problem, when we want to use the same shader +
 * the same mesh type + instancing, but just different color / texture / shader parameter
 */
class TextureRenderer {

    private:
        /**
         * INSTANCED RENDERING
         *
         * Map that keeps unique [mesh-shader] pairs for instanced rendering
         *
         * a - mesh type            const char *   (mesh enum string or mesh path)
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
        std::vector<std::pair<std::pair<std::shared_ptr<Mesh>, const char *>, Transform>> meshesToRender;

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