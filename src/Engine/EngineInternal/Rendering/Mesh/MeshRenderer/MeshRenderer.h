#pragma once

#include <glad.h>
#include "Engine/EngineInternal/Rendering/Mesh/Mesh.h"

#include <Components/Component.h>
#include <Engine/EngineInternal/Rendering/Shading/ShaderType.h>

class MeshRenderer : public Component {

    private:

        std::shared_ptr<Mesh> mesh;

        GLuint vao = 0;
        GLuint vbo = 0;
        GLuint uvbo = 0;
        GLuint nbo = 0;
        GLuint model_matrices_vbo = 0;
        GLuint color_vectors_vbo = 0;
        GLuint ibo = 0;

        GLuint textureId = 0;

    public:

        //////////////////////////////// Shader /////////////////////////////////
        std::shared_ptr<Shader> shader;
        /////////////////////////////////////////////////////////////////////////

        //////////////////////////////// Options ////////////////////////////////
        Projection projection = PERSPECTIVE;
        ShaderType shaderType = AMBIENT;

        /// Single texture path
        const char * texture = nullptr;

        /// Multiple texture paths (e.g. for cubemap)
        std::vector<std::string> paths;

        /// Flags
        bool disableNormals = false;
        bool cubeMap = false;
        bool enableBoundingBox = true;

        /// Base shader color
        glm::vec4 color = glm::vec4(1.0, 0.0, 1.0, 1.0);

        /// Shader update method
        std::function<void(const std::shared_ptr<Shader> &)> shaderInit = [](const std::shared_ptr<Shader> & func) {};

        /////////////////////////////////////////////////////////////////////////

        void init(const std::shared_ptr<Mesh> & mesh);

        void prepare();

        void CreateVertexAttributeObject();
        void CreateIndexBuffer();
        void CreateVertexBuffer();
        void CreateUVBuffer();
        void CreateNormalsBuffer();
        void CreateModelMatricesBuffer();
        void CreateColorBuffer();

        void UpdateModelMatrices();
        void UpdateColorVectors();

        void loadTexture(const char * path);
        void loadCubeMap(const std::vector<std::string> & paths);

        void render();
        void renderInstanced(int instancesCount);
        void renderInstanced(GLenum renderMode, int indicesCount, int instanceCount);
        void render(GLenum renderMode, int indicesCount);

        std::string getShaderTypeStr();

};