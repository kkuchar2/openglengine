#pragma once

#include <cmath>
#include <memory>
#include <functional>
#include <map>
#include <thread>
#include <limits>

#include "Shading/Shader.h"
#include "../Utils/Logging/Logger.h"
#include "../Utils/OBJ/tiny_obj_loader.h"
#include "../Utils/TextureLoader.h"
#include "../Window/Input/Component.h"

struct Transform {
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
};

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

        GLenum mode = GL_TRIANGLES;

        bool disableNormals = false;
        bool prepared = false;

        GLuint textureId = 0;

        std::shared_ptr<Shader> shader;

        GLuint vao = 0;
        GLuint vbo = 0;
        GLuint uvbo = 0;
        GLuint nbo = 0;
        GLuint ibo = 0;

        float * pVertexPosBufferData {};

        Transform transform;

        ShaderFunc shaderInit = [](const std::shared_ptr<Shader> & shaderFunc) {};

        Mesh(const char * path);

        Mesh();

        void prepare();

        void CreateVertexAttributeObject();
        void CreateIndexBuffer();

        void CreateVertexBuffer();

        void CreateUVBuffer();

        void CreateNormalsBuffer();

        static void UnbindVertexAtrributeObject();

        void copyVertifcesToBuffer();

        void UpdateVertexBuffer();

        virtual void Render();
        void Render(GLenum renderMode, int count);

        void loadTexture(const char * path);

        BoundingBox calculateBoundingBox();

        void calculateNormals();

        void loadMesh(const char * path);

        static std::shared_ptr<Mesh> create(const char * path);
};