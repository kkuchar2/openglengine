#pragma once

#include <glad.h>

#include "SceneDefinition/Scene.h"

#include "Camera/OrtographicCamera.h"
#include "Camera/PerspectiveCamera.h"
#include "InstancedMeshInfo.h"

#include <Primitives/Quad.h>

#include <thread>
#include <future>

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
 */

using ShaderToMeshesMap = std::map<ShaderType, std::shared_ptr<InstancedMeshInfo>>;

class Renderer {

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

        std::map<const char *, std::map<ShaderType, std::shared_ptr<InstancedMeshInfo>>> map;

        /**
         * CLASSIC RENDERING
         *
         * Vector for meshes, that will be rendered without instancing
         */
        std::vector<std::pair<std::shared_ptr<Mesh>, std::shared_ptr<GameObject>>> meshesToRender;

        std::shared_ptr<BaseCamera> getCamera(const Projection & projection);

    public:

        double width = 1.0;
        double height = 1.0;

        GLuint texture = 0;
        GLuint dephRenderBuffer = 0;
        GLuint framebufferName = 0;

        std::shared_ptr<OrtographicCamera> ortographicCamera;
        std::shared_ptr<PerspectiveCamera> perspectiveCamera;

        std::vector<std::shared_ptr<GameObject>> objectsToRender;

        explicit Renderer(const std::shared_ptr<Window> & window);

        void addScene(const std::shared_ptr<Scene> & scene);

        void prepare();

        void preprocessScenes();

        void render();

        void createFrameBuffer();

        void renderToTexture();

        void updateSize(const glm::vec2 & newSize);

        void renderAllMeshes();

        void updateCameras();

        void updateModelMatrices(int startRange, int endRange);

        void logRenderMap();

        ShaderToMeshesMap createShaderToMeshesMap(const ShaderType & shaderType, const std::shared_ptr<Mesh> & mesh, const Projection & projection, const Transform & transform);
};