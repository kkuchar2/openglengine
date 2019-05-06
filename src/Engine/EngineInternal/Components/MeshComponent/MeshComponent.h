#pragma once

#include <string>
#include <glm/glm/vec4.hpp>
#include <memory>

#include <Rendering/Shading/ShaderType.h>
#include <Engine/EngineInternal/Rendering/Mesh/MeshType.h>

#include "../Component.h"

class MeshComponent : public Component {
    public:
        std::string path;
        MeshType meshType = NONE;
        ShaderType shaderType = AMBIENT;
        glm::vec4 color = glm::vec4(1.0, 1.0, 1.0, 1.0);
        const char * texture = nullptr;

        bool disableNormals = false;
        bool cubeMap = false;
        bool disableBoundingBox = false;

        std::string meshTypeStr;
        std::string shaderTypeStr;
        std::string shaderMeshTypeId;

        MeshComponent();

        MeshComponent(const MeshType & meshType, const ShaderType & shaderType, const glm::vec4 & color);

        MeshComponent(const std::string & path, const ShaderType & shaderType, const glm::vec4 & color);

        std::string getMeshTypeStr();
        std::string getShaderTypeStr();

        void updateIds();

        static std::shared_ptr<MeshComponent> of(const MeshType & meshType, const ShaderType & shaderType, const glm::vec4 & color);

        static std::shared_ptr<MeshComponent> of(const char * path, const ShaderType & shaderType, const glm::vec4 & color);
};