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

        GLenum mode = GL_TRIANGLES;

        MeshType type = NONE;
        Projection projection = PERSPECTIVE;

        bool disableNormals = true;
        bool prepared = false;
        bool isInstanced = true;

        GLuint textureId = 0;

        std::shared_ptr<Shader> shader;

        GLuint vao = 0;
        GLuint vbo = 0;
        GLuint uvbo = 0;
        GLuint nbo = 0;
        GLuint posvbo = 0;
        GLuint ibo = 0;

        float * pVertexPosBufferData {};


        ShaderFunc shaderInit = [](const std::shared_ptr<Shader> & shaderFunc) {};

        Mesh(const char * path);

        Mesh();

        void prepare();

        void CreateVertexAttributeObject();
        void CreateIndexBuffer();
        void CreateVertexBuffer();
        void CreateUVBuffer();
        void CreateNormalsBuffer();
        void CreatePositionBuffer();

        void copyVertifcesToBuffer();
        void UpdateVertexBuffer();

        virtual void Render(int instancesCount);
        void Render(GLenum renderMode, int indicesCount, int instanceCount);

        void loadTexture(const char * path);

        void calculateNormals();

        void loadFromResource(const char * path);

        static std::shared_ptr<Mesh> create(const char * path);

        static std::shared_ptr<Mesh> of(const std::shared_ptr<MeshPrototype> & proto, const Projection & projection);
};