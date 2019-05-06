#include "MeshComponent.h"

MeshComponent::MeshComponent() = default;

MeshComponent::MeshComponent(const MeshType & meshType, const ShaderType & shaderType, const glm::vec4 & color) {
    this->meshType = meshType;
    this->shaderType = shaderType;
    this->color = color;
    this->meshTypeStr = getMeshTypeStr();
    this->shaderTypeStr = getShaderTypeStr();
    this->shaderMeshTypeId = meshTypeStr + std::string("_") + shaderTypeStr;
}

MeshComponent::MeshComponent(const std::string & path, const ShaderType & shaderType, const glm::vec4 & color) {
    this->path = path;
    this->meshType = RESOURCE;
    this->shaderType = shaderType;
    this->color = color;
    this->meshTypeStr = getMeshTypeStr();
    this->shaderTypeStr = getShaderTypeStr();
    this->shaderMeshTypeId = meshTypeStr + std::string("_") + shaderTypeStr;
}

std::string MeshComponent::getMeshTypeStr() {

    switch(meshType) {
        case LINE: return "line";
        case QUAD: return "quad";
        case CUBE: return "cube";
        case SURFACE: return "surface";
        case SKYBOX: return "skybox";
        case RESOURCE: return path;
        case NONE: return "";
        default: return "";
    }
}

std::string MeshComponent::getShaderTypeStr() {
    switch(shaderType) {
        case AMBIENT: return "ambient";
        case PHONG: return "phong";
        case GRID: return "grid";
        case TEXTURE: return "texture";
        case TEXTURE_CUBE: return "texture_cube";
        case MANDELBROT: return "mandelbrot";
    }
}

void MeshComponent::updateIds() {
    this->meshTypeStr = getMeshTypeStr();
    this->shaderTypeStr = getShaderTypeStr();
    this->shaderMeshTypeId = meshTypeStr + std::string("_") + shaderTypeStr;
}

std::shared_ptr<MeshComponent>
MeshComponent::of(const MeshType & meshType, const ShaderType & shaderType, const glm::vec4 & color) {
    return std::make_shared<MeshComponent>(meshType, shaderType, color);
}

std::shared_ptr<MeshComponent>
MeshComponent::of(const char * path, const ShaderType & shaderType, const glm::vec4 & color) {
    return std::make_shared<MeshComponent>(path, shaderType, color);
}