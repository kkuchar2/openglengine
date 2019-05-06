#pragma once

#include "MeshComponent.h"

class SurfaceMeshComponent : public MeshComponent {
    public:
        float width = 10.0;
        float height = 10.0;

        SurfaceMeshComponent(const ShaderType & shaderType, const glm::vec4 & color) : MeshComponent(SURFACE, shaderType, color) {}

        static std::shared_ptr<SurfaceMeshComponent> of(const ShaderType & shaderType, const glm::vec4 & color) {
            return std::make_shared<SurfaceMeshComponent>(shaderType, color);
        }
};