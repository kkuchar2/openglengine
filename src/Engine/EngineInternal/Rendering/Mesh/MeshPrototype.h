#pragma once

#include <Rendering/Shading/ShaderType.h>
#include <Component.h>
#include <memory>
#include <glm/glm/vec4.hpp>

#include "MeshType.h"

class MeshPrototype : public Component {
    public:
        std::string path;
        MeshType meshType = NONE;
        ShaderType shaderType = AMBIENT;
        glm::vec4 color = glm::vec4(1.0, 1.0, 1.0, 1.0);
        const char * texture = nullptr;
        bool instanced = false;
        bool disableNormals = false;
        bool cubeMap = false;

        std::string meshTypeStr;
        std::string shaderTypeStr;
        std::string shaderMeshTypeId;

        MeshPrototype();

        MeshPrototype(const MeshType & meshType, const ShaderType & shaderType, const glm::vec4 & color);

        MeshPrototype(const std::string & path, const ShaderType & shaderType, const glm::vec4 & color);

        std::string getMeshTypeStr();
        std::string getShaderTypeStr();

        void updateIds();

        static std::shared_ptr<MeshPrototype> of(const MeshType & meshType, const ShaderType & shaderType, const glm::vec4 & color) {
            return std::make_shared<MeshPrototype>(meshType, shaderType, color);
        }

        static std::shared_ptr<MeshPrototype> of(const char * path, const ShaderType & shaderType, const glm::vec4 & color) {
            return std::make_shared<MeshPrototype>(path, shaderType, color);
        }
};