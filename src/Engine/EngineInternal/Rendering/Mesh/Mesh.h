#pragma once

#include <cmath>
#include <memory>
#include <functional>
#include <map>
#include <thread>
#include <limits>
#include <Rendering/Camera/Projection.h>

#include "Shading/Shader.h"

#include "../../Utils/OBJ/tiny_obj_loader.h"
#include "../../Utils/TextureLoader.h"
#include "Component.h"
#include "MeshType.h"
#include "MeshPrototype.h"


struct TriangleInfo {
    float angle;
    glm::vec3 normal;
};

struct BoundingBox {
    glm::vec3 size;
    glm::vec3 center;
    glm::vec3 rotation;
};

typedef std::shared_ptr<Shader> & ShaderPtrRef;
typedef std::function<void(ShaderPtrRef)> ShaderFunc;

class Mesh : public Component {
    public:

        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        std::vector<float> uvs;
        std::vector<float> normals;

        std::vector<glm::mat4> modelMatrices;

        const char * meshType = "default";

        GLenum mode = GL_TRIANGLES;

        Projection projection = PERSPECTIVE;

        bool disableNormals = true;
        bool prepared = false;
        bool cubeMap = false;

        GLuint textureId = 0;

        std::shared_ptr<Shader> shader;

        GLuint vao = 0;
        GLuint vbo = 0;
        GLuint uvbo = 0;
        GLuint nbo = 0;
        GLuint model_matrices_vbo = 0;
        GLuint ibo = 0;

        ShaderFunc shaderInit = [](const std::shared_ptr<Shader> & shaderFunc) {};

        explicit Mesh(const char * path);

        Mesh();

        void prepare();

        void CreateVertexAttributeObject();
        void CreateIndexBuffer();
        void CreateVertexBuffer();
        void CreateUVBuffer();
        void CreateNormalsBuffer();
        void CreateModelMatricesBuffer();

        virtual void render();

        virtual void renderInstanced(int instancesCount);

        void renderInstanced(GLenum renderMode, int indicesCount, int instanceCount);

        void UpdateModelMatrices();

        void render(GLenum renderMode, int indicesCount);

        void loadTexture(const char * path);
        void loadCubeMap(const std::vector<std::string> & paths);

        void calculateNormals();

        void loadFromResource(const char * path);

        static std::shared_ptr<Mesh> create(const char * path);
};