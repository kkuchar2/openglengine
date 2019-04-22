#pragma once

#include "MeshPrototype.h"

class SurfacePrototype : public MeshPrototype {
    public:
        float width = 10.0;
        float height = 10.0;

        SurfacePrototype(const ShaderType & shaderType, const glm::vec4 & color) : MeshPrototype(SURFACE, shaderType, color) {}

        static std::shared_ptr<SurfacePrototype> of(const ShaderType & shaderType, const glm::vec4 & color) {
            return std::make_shared<SurfacePrototype>(shaderType, color);
        }
};