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


class Mesh {
    public:
        std::string meshId = "default";

        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        std::vector<float> uvs;
        std::vector<float> normals;

        std::vector<glm::mat4x4> modelMatrices;
        std::vector<glm::vec4> colorVectors;

        GLenum renderingMode = GL_TRIANGLES;

        bool prepared = false;

        Mesh();

        Mesh(const std::string & path);

        void loadFromFile(const std::string & path);
};