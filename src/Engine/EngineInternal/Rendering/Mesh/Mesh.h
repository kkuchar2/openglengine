#pragma once

#include <cmath>
#include <memory>
#include <functional>
#include <map>
#include <thread>
#include <limits>
#include <tinyobj/tiny_obj_loader.h>

#include <Engine/EngineInternal/Rendering/Projection.h>

#include "Shading/Shader.h"
#include "Utils/TextureLoader/TextureLoader.h"
#include "MeshType.h"
#include "Engine/EngineInternal/Scene/Transform.h"

typedef std::function<void(std::shared_ptr<Shader> &)> ShaderFunc;

class Mesh {
    public:

        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        std::vector<float> uvs;
        std::vector<float> normals;

        std::vector<glm::mat4x4> modelMatrices;
        std::vector<glm::vec4> colorVectors;

        std::string meshType = "default";
        std::string shaderType = "default";

        GLenum mode = GL_TRIANGLES;

        Projection projection = PERSPECTIVE;

        bool disableNormals = true;
        bool prepared = false;
        bool cubeMap = false;

        std::shared_ptr<Shader> shader;

        ShaderFunc shaderInit = [](const std::shared_ptr<Shader> & shaderFunc) {};

        explicit Mesh(const std::string & path);

        Mesh();

        void loadFromResource(const std::string & path);

        static std::shared_ptr<Mesh> create(const char * path);
};