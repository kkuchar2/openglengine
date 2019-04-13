#pragma once

#include <Rendering/Shading/ShaderType.h>
#include <Component.h>
#include <memory>
#include <glm/glm/vec4.hpp>

#include "MeshType.h"

class MeshPrototype : public Component {
    public:
        const char * path = nullptr;
        MeshType meshType = NONE;
        ShaderType shaderType = COLOR_INSTANCED;
        glm::vec4 color = glm::vec4(1.0, 1.0, 1.0, 1.0);
        const char * texture = nullptr;
        bool instanced = false;
        bool disableNormals = false;

        MeshPrototype();

        MeshPrototype(const MeshType & meshType, const ShaderType & shaderType, const glm::vec4 & color);

        MeshPrototype(const char * path, const ShaderType & shaderType, const glm::vec4 & color);

        const char * getMeshType();

        static std::shared_ptr<MeshPrototype> of(const MeshType & meshType, const ShaderType & shaderType, const glm::vec4 & color) {
            return std::make_shared<MeshPrototype>(meshType, shaderType, color);
        }

        static std::shared_ptr<MeshPrototype> of(const char * path, const ShaderType & shaderType, const glm::vec4 & color) {
            return std::make_shared<MeshPrototype>(path, shaderType, color);
        }
};